#include "config.h"

void notFoundError() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr); // Pastikan menggunakan font yang sesuai
    u8g2.drawStr(10, 30, "USER TIDAK");
    u8g2.drawStr(8, 50, "DITEMUKAN!");
    u8g2.sendBuffer();
    
    unsigned long startTime = millis();
    while (millis() - startTime < 2000) {
        // Biarkan tampilan tetap selama 2 detik tanpa delay() blocking
    }
}
