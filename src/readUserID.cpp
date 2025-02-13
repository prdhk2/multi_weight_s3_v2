#include "config.h"

void readUserID() {
    id_input = "";  // Reset input user
    String lastInput = "";  // Menyimpan input terakhir untuk optimasi tampilan
    unsigned long startTime = millis();  // Waktu mulai untuk timeout

    // Tampilkan layar awal hanya sekali
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(2, 28, "MASUKAN");
    u8g2.drawStr(2, 45, "ID USER :");
    u8g2.sendBuffer();

    while (millis() - startTime < 30000) {  // Timeout 30 detik jika tidak ada input
        char key = kpd.getKey();  // Baca tombol keypad

        if (key) {
            switch (key) {
                case '*':  
                    menuDisplay();  // Kembali ke menu utama
                    return;
                case '#':  
                    if (!id_input.isEmpty()) {
                        id_input.remove(id_input.length() - 1);  // Hapus karakter terakhir
                    }
                    break;
                default:
                    if (id_input.length() < 5 && isDigit(key)) {  
                        id_input += key;  // Tambahkan angka jika belum mencapai batas
                    }
                    break;
            }

            // Perbarui tampilan hanya jika input berubah
            if (id_input != lastInput) {
                lastInput = id_input;
                u8g2.clearBuffer();
                u8g2.setDrawColor(1);
                u8g2.drawStr(2, 28, "MASUKAN");
                u8g2.drawStr(2, 45, "ID USER :");
                u8g2.drawStr(80, 45, id_input.c_str());
                u8g2.sendBuffer();
            }

            Serial.print("ID Input Sekarang: ");
            Serial.println(id_input);
        }

        // Cek tombol ENTER
        if (searchAction()) return;
    }

    Serial.println("Timeout: Tidak ada input selama 30 detik");
    menuDisplay();  // Kembali ke menu jika timeout
}

// 🚀 Optimized `searchAction()`
bool searchAction() {
    static unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 50;

    bool currentState = digitalRead(ENTER_BUTTON);
    if (currentState == HIGH && lastStateEnterButton == LOW && millis() - lastDebounceTime > debounceDelay) {
        lastDebounceTime = millis();

        if (!id_input.isEmpty()) {
            int id_user = id_input.toInt();
            Serial.print("ID yang dimasukkan: ");
            Serial.println(id_user);
            searchID(id_user);  // Panggil pencarian user
            id_input = "";  // Reset input setelah pencarian
            return true;  
        } else {
            Serial.println("User ID tidak boleh kosong");
        }
    }

    lastStateEnterButton = currentState;
    return false;  
}