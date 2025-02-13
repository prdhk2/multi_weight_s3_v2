#include "config.h"

void serverResponseDisplay(int responseCode) {
    unsigned long startTime = millis();  // Mulai hitungan waktu saat fungsi dipanggil

    while (millis() - startTime < 3000) {  // Tampilkan selama 3 detik
        u8g2.clearBuffer();
        u8g2.setDrawColor(1);
        u8g2.setFont(u8g2_font_ncenB10_tr);

        if (responseCode == 200) {
            u8g2.drawStr(7, 37, "Data Terkirim!");
        } else {
            u8g2.drawStr(13, 28, "Gagal! Kode:");
            char responseStr[5];
            itoa(responseCode, responseStr, 10);
            u8g2.drawStr(58, 43, responseStr);
        }

        u8g2.sendBuffer();
        delay(10);
    }
    yield();

    u8g2.clearBuffer();
    u8g2.sendBuffer();

    displayWeight();
}
