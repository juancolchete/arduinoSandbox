#include <M5StickCPlus.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(3);
}

void newYearEve(){
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("\n Happy New \n Year's Eve!!");
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.Rtc.GetBm8563Time();
  int hour = M5.Rtc.Hour;
  int minute = M5.Rtc.Minute;
  int second = M5.Rtc.Second;
  if(hour == 20){
    newYearEve();
  }
  if(hour == 21){
    newYearEve();
  }
  if(hour == 0){
    newYearEve();
  }
  delay(1000);
}
