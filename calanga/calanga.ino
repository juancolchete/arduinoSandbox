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
bool getBatteryCharging(void)
{
  float c = M5.Axp.GetVapsData() * 1.4 / 1000;
  return c > 4.5;
}

char *calanga[12];
bool right = true;
bool setDefaultColor = false;
int lastHour;
int lastMinute;
bool lastPower;
void loop() {
  // put your main code here, to run repeatedly:
  if(right == true){
    right = false;
    calanga[0] = "                   .";
    calanga[1] = "     _.--._       /|";
    calanga[2] = "   .'()..()`.    / /";
    calanga[3] = "  ( `-.__.-' )  ( ( ";
    calanga[4] = "   \\        /    \\ \\";
    calanga[5] = "    \\      /      ) )";
    calanga[6] = "  .' -.__.- `.-.-'_.'";
    calanga[7] = ".'  /-____-\\  `.-'";
    calanga[8] = "\\  /-.____.-\\  /-.";
    calanga[9] = " \\ \\`-.__.-'/ /\\|\\|";
    calanga[10] = ".'  `.      .'  `.";
    calanga[11] = "|/\\/\\|    |/\\/\\|";
  }else{
    right = true;
    calanga[0] = " .                      ";
    calanga[1] = "| |       _.--._        ";
    calanga[2] = "| |     .'()..()`.      ";
    calanga[3] = "| |    ( `-.__.-' )     ";
    calanga[4] = "| |     \\        /     ";
    calanga[5] = " \\ \\     \\      /    ";
    calanga[6] = "   \\ \\ .' -.__.- `    ";
    calanga[7] = " .'----.'  /-____-\\    ";
    calanga[8] = ".'.---.\\  /-.____.-\\  ";
    calanga[9] = "|/\\|\\|\\ \\`-.____.-'\\";
    calanga[10] = "     .' `.      .' `.   ";
    calanga[11] = "    |/\\/\\|      |/\\/\\|";
  }
  M5.Lcd.setCursor(0, 30, 1);
  M5.Lcd.printf(calanga[0]);
  M5.Lcd.setCursor(0, 40, 1);
  M5.Lcd.printf(calanga[1]);
  M5.Lcd.setCursor(0, 50, 1);
  M5.Lcd.printf(calanga[2]);
  M5.Lcd.setCursor(0, 60, 1);
  M5.Lcd.printf(calanga[3]);
  M5.Lcd.setCursor(0, 70, 1);
  M5.Lcd.printf(calanga[4]);
  M5.Lcd.setCursor(0, 80, 1);
  M5.Lcd.printf(calanga[5]);
  M5.Lcd.setCursor(0, 90, 1);
  M5.Lcd.printf(calanga[6]);
  M5.Lcd.setCursor(0, 100, 1);
  M5.Lcd.printf(calanga[7]);
  M5.Lcd.setCursor(0, 110, 1);
  M5.Lcd.printf(calanga[8]);
  M5.Lcd.setCursor(0, 120, 1);
  M5.Lcd.printf(calanga[9]);
  M5.Lcd.setCursor(0, 130, 1);
  M5.Lcd.printf(calanga[10]);
  M5.Lcd.setCursor(0, 140, 1);
  M5.Lcd.printf(calanga[11]);
  M5.Lcd.setCursor(0, 150, 1);
  M5.Rtc.GetBm8563Time();
  M5.Lcd.setCursor(30, 180, 1);
  M5.Lcd.printf("%02d : %02d : %02d", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
  M5.Lcd.setCursor(10, 200, 1);
  M5.Lcd.printf("battery: %.2f%s",getBatteryLevel(),"%");
  M5.Lcd.setCursor(10, 210, 1);
  M5.Lcd.printf("charging: %d",getBatteryCharging());
  if(lastHour != M5.Rtc.Hour){
    m5.Lcd.fillScreen(RED);
    M5.Beep.beep();
    lastHour = M5.Rtc.Hour;
    setDefaultColor = true;
  }
  if(lastMinute != M5.Rtc.Minute){
    m5.Lcd.fillScreen(BLUE);
    lastMinute = M5.Rtc.Minute;
    setDefaultColor = true;
  }
  if(lastPower != getBatteryCharging()){
    lastPower = getBatteryCharging();
    if(lastPower){
      m5.Lcd.fillScreen(GREEN);
    }else{
      m5.Lcd.fillScreen(RED);
    }
    setDefaultColor = true;
  }
  delay(1000);
  if(setDefaultColor == true){
    M5.Beep.mute();
    m5.Lcd.fillScreen(BLACK);
    setDefaultColor = false;
  }
}