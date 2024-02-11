#include "M5StickCPlus.h"
#include <WiFi.h>
#include ".\conf.h"



void setup() {
  M5.begin(true, true, true);
  M5.Lcd.setTextSize(3);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      m5.Lcd.fillScreen(WHITE);
      delay(500);
      m5.Lcd.fillScreen(BLACK);
  }
  M5.Lcd.print("Connected");
}

void loop() {
}
