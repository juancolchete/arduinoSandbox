#include "M5StickCPlus.h"
#include <WiFi.h>
#include ".\conf.h"



void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2.5);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      m5.Lcd.fillScreen(WHITE);
      delay(1000);
      m5.Lcd.fillScreen(BLACK);
  }
  M5.Lcd.print("Connected");
}

void loop() {
}
