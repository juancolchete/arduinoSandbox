#include <M5StickCPlus.h>

#include <string>
void setup() {
  // put your setup code here, to run once:
  M5.begin();
}
double getBatteryLevel(void)
{
  float b = M5.Axp.GetVbatData() * 1.1 / 1000;
  int battery = ((b - 3.0) / 1.2) * 100;
  return battery;
}
int pressedTimes=0;
uint16_t colors[6] = {0xFFFF,0x001F,0xFC9F,0xFFE0,0x0451,0x7800};
void loop() {
  if(digitalRead(M5_BUTTON_HOME) == false){
    m5.Lcd.fillScreen(colors[pressedTimes]);
    pressedTimes++;
    if(pressedTimes >= 7){
      pressedTimes = 0;
      m5.Lcd.fillScreen(0x0000);
    }
    delay(100);
  };
  M5.Lcd.setCursor(10, 200, 1);
  M5.Lcd.printf("battery: %.2f%s",getBatteryLevel(),"%");
}