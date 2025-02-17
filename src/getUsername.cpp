#include "config.h"

const char* serverUrl = "http://192.168.1.9/timbangan/api.php";  // Ganti dengan URL API-mu

String getusername(int userId) {
 if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "?action=get_user&id=" + String(userId);
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String payload = http.getString();
      http.end();

      // Gunakan JsonDocument
      DynamicJsonDocument doc(512);
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("JSON Parsing Failed: ");
        Serial.println(error.c_str());
        return "";
      }

      // Ambil nilai dari kunci "username"
      String username = doc["username"].as<String>();
      return username;
    } else {
      http.end();
      return "";
    }
  } else {
    return "";
  }
}
