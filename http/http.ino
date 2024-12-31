// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include ".\conf.h"
#include <M5StickCPlus.h>
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";
uint16_t color = BLACK;
bool right = true;
bool running = false;
char *calanga[12];
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>RBG ESP32 M5 STICKCPLUS SEVER</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Output - GPIO 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"1\" " + outputState(2) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(4) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"3\" " + outputState(33) + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

void showMsg(String msg,uint16_t color){
  delay(200);
  m5.Lcd.fillScreen(color);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(msg);
}

void setup(){
  M5.begin();
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    m5.Lcd.fillScreen(BLACK);
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      if(inputMessage1 == "1" && inputMessage2 == "1"){
        color=RED;
        m5.Lcd.fillScreen(RED);
      }else if(inputMessage1 == "2" && inputMessage2 == "1"){
        color=GREEN;
        m5.Lcd.fillScreen(GREEN);
      }else if(inputMessage1 == "3" && inputMessage2 == "1"){
        color=BLUE;
        m5.Lcd.fillScreen(BLUE);
      }else if (inputMessage1 == "4" && inputMessage2 == "1"){
        M5.Lcd.setRotation(1);
        M5.Lcd.setTextSize(3);
        m5.Lcd.fillScreen(color);
        showMsg("\n H",color);
        showMsg("\n Ha",color);
        showMsg("\n Hap",color);
        showMsg("\n Happ",color);
        showMsg("\n Happy",color);
        showMsg("\n Happy ",color);
        showMsg("\n Happy N",color);
        showMsg("\n Happy Ne",color);
        showMsg("\n Happy New",color);
        showMsg("\n Happy New \n Y",color);
        showMsg("\n Happy New \n Ye",color);
        showMsg("\n Happy New \n Yea",color);
        showMsg("\n Happy New \n Year",color);
        showMsg("\n Happy New \n Year'",color);
        showMsg("\n Happy New \n Year's",color);
        showMsg("\n Happy New \n Year's E",color);
        showMsg("\n Happy New \n Year's Ev",color);
        showMsg("\n Happy New \n Year's Eve",color);
        showMsg("\n Happy New \n Year's Eve!",color);
        m5.Lcd.fillScreen(WHITE);
        m5.Lcd.fillScreen(BLACK);
        m5.Lcd.fillScreen(WHITE);
        m5.Lcd.fillScreen(BLACK);
        m5.Lcd.fillScreen(color);
      }else if (inputMessage1 == "5" && inputMessage2 == "1"){
        running = true;
      }else{
        m5.Lcd.fillScreen(BLACK);
        running = false;
      }
    }else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "JC was here");
  });

  // Start server
  server.begin();
}

void loop() {
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
  if(running){
    M5.Lcd.setTextSize(1);
    M5.Lcd.setRotation(1);
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
}
  