#include "config.h"

void displayWeight() {
    static unsigned long lastUpdate = 0;
    constexpr unsigned long updateInterval = 500;

    while (true) {  
        float weight = readWeight();  

        // Update tampilan hanya jika berat berubah atau setelah interval tertentu
        if (weight != lastWeight || millis() - lastUpdate > updateInterval) {
            lastUpdate = millis();
            lastWeight = weight;
            updateDisplay(weight);
        }

        // Cek tombol keypad "*" untuk kembali ke menu atau tombol "Kirim"
        if (checkKeyPress() || checkSendButton()) {
            return;
        }

        yield();  // Beri waktu ke sistem ESP
        delay(10); // Kurangi beban CPU
    }
}

void updateDisplay(float weight) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(2, 8, "User Ditemukan !");
    u8g2.drawStr(2, 20, "ID");
    u8g2.drawStr(40, 20, ":");
    u8g2.drawStr(50, 20, String(id_user).c_str());
    u8g2.drawStr(2, 33, "Nama");
    u8g2.drawStr(40, 33, ":");
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(50, 35, username.c_str());
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(2, 46, "Berat");
    u8g2.drawStr(40, 46, ":");
    u8g2.setFont(u8g2_font_ncenB10_tr);

    char weightStr[10];
    if (isnan(weight)) {
        u8g2.drawStr(50, 49, "N/A");
    } else {
        dtostrf(weight, 4, 2, weightStr);
        u8g2.drawStr(50, 49, weightStr);
    }

    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(105, 46, "/Kg");
    u8g2.drawStr(1, 61, "Kembali");
    u8g2.drawStr(103, 61, "Kirim");

    u8g2.sendBuffer();
    yield();
}

bool checkKeyPress() {
    char key = kpd.getKey();  // Baca input dari keypad

    if (key) {  // Cek apakah ada tombol ditekan
        Serial.print("Keypad ditekan: ");
        Serial.println(key);
    }

    if (key == '*') {  // Jika tombol '*' ditekan, kembali ke menu
        Serial.println("Tombol '*' ditekan, kembali ke menu...");
        menuDisplay();
        return true;
    }

    return false;
}

// 🔹 Fungsi untuk mengecek tombol "Kirim"
bool checkSendButton() {
    static unsigned long lastDebounceTime = 0;
    if (digitalRead(SEND_BUTTON) == LOW) {  // INPUT_PULLUP, LOW berarti ditekan
        if (millis() - lastDebounceTime > 50) {
            if (httpState == HTTP_IDLE) {
                Serial.println("Tombol 'Kirim' ditekan, mengirim data...");
                int responseCode = kirimData(id_user, username, lastWeight);
                Serial.printf("Response Code: %d\n", responseCode);
                serverResponseDisplay(responseCode);
                return true;
            }
        }
    }
    lastDebounceTime = millis();
    return false;
}
