#include "config.h"

void menuDisplay() {
    id_menu = "";  // Reset input menu sebelum menerima angka

    while (true) {  // Loop utama untuk membaca input keypad secara real-time
        // Tampilkan menu
        u8g2.clearBuffer();
        u8g2.drawStr(55, 8, "Menu:");
        u8g2.setFont(u8g2_font_ncenB10_tr);
        u8g2.drawStr(2, 25, "1. Registrasi");
        u8g2.drawStr(2, 42, "2. Menimbang");

        u8g2.setFont(u8g2_font_5x7_tr);
        u8g2.drawStr(2, 58, "Pilih menu: ");
        u8g2.drawStr(60, 58, id_menu.c_str());
        u8g2.sendBuffer();

        char key = kpd.getKey();  // Baca tombol keypad

        if (key) {
            Serial.print("Key Pressed: ");
            Serial.println(key);

            switch (key) {
                case '*':  // Reset pilihan menu
                    Serial.println("Tombol * ditekan, kembali ke menu utama");
                    id_menu = "";
                    break;
                case '#':  // Hapus karakter terakhir
                    if (!id_menu.isEmpty()) {
                        id_menu.remove(id_menu.length() - 1);
                    }
                    break;
                default:
                    if (id_menu.isEmpty() && isDigit(key)) {
                        id_menu += key;
                    }
                    break;
            }

            Serial.print("ID Menu Sekarang: ");
            Serial.println(id_menu);
        }

        // Cek apakah tombol ENTER ditekan
        currentStateEnterButton = digitalRead(ENTER_BUTTON);
        if (currentStateEnterButton == HIGH && lastStateEnterButton == LOW) {
            delay(50);  // Debounce tombol
            if (digitalRead(ENTER_BUTTON) == HIGH) {
                Serial.println("Tombol ENTER ditekan!");

                if (id_menu == "1") {
                    Serial.println("Menu Registrasi Dipilih");
                    registerDisplay();
                    return;
                } else if (id_menu == "2") {
                    Serial.println("Menu Menimbang Dipilih");
                    readUserID();
                    return;
                } else {
                    Serial.println("Pilihan tidak valid!");
                }
            }
        }

        // Simpan status tombol sebelumnya
        lastStateEnterButton = currentStateEnterButton;
    }
}