#include <M5StickCPlus.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(3);
}

void newYearEve(){
  m5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("\n Happy New \n Year's Eve!");
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.Rtc.GetBm8563Time();
  int hour = M5.Rtc.Hour;
  int minute = M5.Rtc.Minute;
  int second = M5.Rtc.Second;
  if(hour == 0 || hour == 22){
    newYearEve();
  }else{
    m5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.printf("New Year in \n %02d hours\n %02d minutes \n %02d seconds",23-hour,59-minute,59-second);
  }
  delay(1000);
}
