#include <M5StickCPlus.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(2);
}

void ageIncrement(){
  m5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("age = 21");
  delay(500);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.print("age++");
  delay(500);
  M5.Lcd.setCursor(0,40);
  M5.Lcd.print("print(age)");
  delay(500);
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.print("22");
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.Rtc.GetBm8563Time();
  int hour = M5.Rtc.Hour;
  int minute = M5.Rtc.Minute;
  int second = M5.Rtc.Second;
  if(minute == 27){
    ageIncrement();
  }else{
    m5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf(" age++ in \n %02d hours\n %02d minutes \n %02d seconds",0-hour,26-minute,59-second);
  }
  delay(1000);
}
