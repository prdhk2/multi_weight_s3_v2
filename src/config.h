#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <U8g2lib.h>
#include <Keypad.h>
#include "esp_task_wdt.h"

//wifi global configuration
extern const char* ssid;
extern const char* password;
extern const char* serverUrl;

enum WiFiState { 
    DISCONNECTED, 
    CONNECTING, 
    CONNECTED 
};
extern WiFiState wifiState;

enum HttpStatus { 
    HTTP_IDLE, 
    HTTP_SENDING, 
    HTTP_RECEIVING, 
    HTTP_ERROR 
};

// 🔹 Deklarasi variabel global
extern HttpStatus httpState;
extern unsigned long lastHttpMillis;

// Display Configuration
extern U8G2_ST7920_128X64_F_SW_SPI u8g2;

//keypad global variable
const byte ROWS = 4; 
const byte COLS = 3;
extern char hexaKeys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];
extern Keypad kpd;

// Deklarasi tombol ENTER
#define ENTER_BUTTON 4
extern int currentStateEnterButton;
extern bool lastStateEnterButton;

// Deklarasi tombol ENTER
#define SEND_BUTTON 2
extern int currentStateSendButton;
extern bool lastStateSendButton;

// Variabel Global
extern float lastWeight;
extern String id_menu;
extern String id_input;
extern int id_user;
extern String username;
extern unsigned long lastUpdate;

extern int httpResponseCode;

// Fungsi Prototipe
void setupWiFi();

void handleWiFi();

void loadingDisplay();

void menuDisplay();

void inputIdDisplay();

void readUserID();

void displayUserID();

bool searchAction();

void searchID(int new_id);

void notFoundError();

String getusername(int userId);

void registerDisplay();

float readWeight();

void serverResponseDisplay();

// bool checkEnterPress();

bool checkKeyPress();

bool checkSendButton();

bool sendingData();

String extractNumericPart(String inputString);

void displayWeight();

void updateDisplay(float weight);

int kirimData(int id_user, String username, float weight);

void serverResponseDisplay(int responseCode);

#endif
