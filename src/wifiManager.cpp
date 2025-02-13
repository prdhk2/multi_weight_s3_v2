#include "config.h"

const char *ssid        = "RIZQI SEMESTA";
const char *password    = "zerowaste";

void setupWiFi() {
    WiFi.begin(ssid, password);
    wifiState = CONNECTING;
}

void handleWiFi() {
    static unsigned long wifiReconnectMillis = 0;

    if (WiFi.status() != WL_CONNECTED) {
        if (wifiState != DISCONNECTED) {
            Serial.println("WiFi terputus!");
            // u8g2.clearBuffer();
            // u8g2.drawStr(2, 33, "Wifi Terputus !");
            // u8g2.sendBuffer();
            wifiState = DISCONNECTED;
        }

        if (millis() - wifiReconnectMillis > 5000) {
            wifiReconnectMillis = millis();
            Serial.println("Mencoba koneksi ulang...");
            WiFi.disconnect();
            WiFi.reconnect();
            // u8g2.clearBuffer();
            // u8g2.drawStr(2, 33, "Menghubungkan Ulang !");
            // u8g2.sendBuffer();
        }
    } else {
        if (wifiState != CONNECTED) {
            Serial.println("WiFi Tersambung!");
            // u8g2.clearBuffer();
            // u8g2.drawStr(2, 33, "Wifi Terhubung !");
            // u8g2.sendBuffer();
            wifiState = CONNECTED;
        }
    }
}
