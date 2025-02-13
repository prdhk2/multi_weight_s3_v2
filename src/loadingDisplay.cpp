#include "config.h"

void loadingDisplay() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.setFontMode(1); // Bold 
    u8g2.drawStr(8, 15, "... Loading data ...");
    u8g2.drawStr(45, 25, "");
    u8g2.setFontMode(0); // reset Bold

    int barWidth    = 100;
    int barHeight   = 10;

    for (int i = 0; i < barWidth; i++) {
        u8g2.drawBox(14 + i, 40, 1, barHeight);
        u8g2.sendBuffer();
        delay(3);
    }
}