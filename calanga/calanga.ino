#include <M5StickCPlus.h>
#include <string>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

char *calanga[12];
bool right = true;
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
    calanga[0] = " .                  ";
    calanga[1] = "| |       _.--._   ";
    calanga[2] = "| |     .'()..()`. ";
    calanga[3] = "| |    ( `-.__.-' )";
    calanga[4] = "| |     \\        /   ";
    calanga[5] = " \\ \\     \\      /   ";
    calanga[6] = "   \\ \\ .' -.__.- `";
    calanga[7] = " .'    .'  /-____-\\ ";
    calanga[8] = ".'   -.\\  /-.____.-\\ ";
    calanga[9] = "|/\\|\\|\\ \\`-.____.-'\\ ";
    calanga[10] = "     .' `.      .' `.";
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
  delay(1000);
}