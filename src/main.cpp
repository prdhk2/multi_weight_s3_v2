#include "config.h"

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* CLK */ 7, /* MOSI */ 6, /* CS */ 5, /* reset */ U8X8_PIN_NONE);

WiFiState wifiState = DISCONNECTED;

HttpStatus httpState = HTTP_IDLE;  
unsigned long lastHttpMillis = 0;

int httpResponseCode = 0;

unsigned long lastUpdate = 0;
float lastWeight = -1; 

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 9, 10, 11}; 
byte colPins[COLS] = {12, 13, 14};

Keypad kpd = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int currentStateEnterButton;
bool lastStateEnterButton = HIGH;

int currentStateSendButton;
bool lastStateSendButton = HIGH;

String id_menu = "";
String id_input = "";
int id_user = 0;
String username = "";

void setup() {
    Serial.begin(115200); // master 1 Serial for Debugging
    Serial2.begin(4800, SERIAL_8N1, 18, -1, true); // master 1 Serial for Debugging
    setupWiFi();
    u8g2.begin();
    u8g2.setDrawColor(1);
    loadingDisplay();
    pinMode(SEND_BUTTON, INPUT_PULLUP);  // Gunakan internal pull-up
    pinMode(ENTER_BUTTON, INPUT_PULLUP);

    for(byte i = 0; i < COLS; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
    }
    menuDisplay();
}

void loop() {
    handleWiFi(); 
}
