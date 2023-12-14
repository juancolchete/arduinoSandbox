#include <M5StickCPlus.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  m5.Lcd.fillScreen(BLACK);
  M5.Rtc.GetBm8563Time();
  M5.Lcd.setCursor(15, 30, 2);
  M5.Lcd.printf("%02d : %02d : %02d", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
  delay(1000);
  m5.Lcd.fillScreen(WHITE);
}
