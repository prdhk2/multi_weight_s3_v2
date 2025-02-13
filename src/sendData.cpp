#include "config.h"

int kirimData(int id_user, String username, float weight) {

    if (httpState == HTTP_IDLE && WiFi.status() == WL_CONNECTED) {
        httpState = HTTP_SENDING;  // Ubah status jadi SENDING untuk menghindari request bertumpuk

        HTTPClient http;
        http.begin(serverUrl);  // Gunakan serverUrl langsung tanpa konversi String

        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        // Gunakan snprintf untuk format string yang lebih efisien
        char postData[100]; // Sesuaikan ukuran buffer dengan panjang data yang akan dikirim
        snprintf(postData, sizeof(postData), "action=save_data&id_user=%d&username=%s&weight=%.2f", 
                 id_user, username.c_str(), weight);

        int httpResponseCode = http.POST(postData);

        if (httpResponseCode > 0) {
            Serial.printf("HTTP Response Code: %d\n", httpResponseCode);
            Serial.println("Response from server:");
            Serial.println(http.getString());
        } else {
            Serial.printf("Error in sending POST: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();
        httpState = HTTP_IDLE;  // Kembalikan status ke HTTP_IDLE setelah selesai

        serverResponseDisplay(httpResponseCode);

        return httpResponseCode;
    }

    return -1; // Return error code jika tidak memenuhi syarat untuk kirim data
}

void printHttpResponse(HTTPClient& http, int httpResponseCode) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println("Response: " + response);
}