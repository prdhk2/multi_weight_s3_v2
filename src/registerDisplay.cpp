#include "config.h"

void registerDisplay() {
    unsigned long startTime = millis();  // Simpan waktu saat fungsi dipanggil

    while (millis() - startTime < 10000) {  // Tampilkan selama 10 detik
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_5x8_tr);
        u8g2.drawStr(12, 35, "www.rizqisemesta.com");
        u8g2.sendBuffer();
        yield();  // Memberi kesempatan ESP32 untuk menjalankan task lain
    }

    menuDisplay();  // Setelah 10 detik, kembali ke menu
}