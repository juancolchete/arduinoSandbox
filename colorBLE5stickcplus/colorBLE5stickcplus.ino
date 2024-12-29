#include "M5StickCPlus.h"
#include "EasyButton.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
char message[100];

void dumpBLE(char* msg);
String blename;
int COLORS_LIST[19]={0x0000,0x000F,0x03E0,0x03EF,0x7800,0x780F,0x7BE0,0xC618,0x7BEF,0x001F,0x07E0,0x07FF,0xF800,0xF81F,0xFFE0,0xFFFF,0xFDA0,0xB7E0,0xFC9F};
int colori = 0;
#define BTN_A 37
#define BTN_B 39

int press_duration = 2000;
EasyButton Button_A(BTN_A,40);
EasyButton Button_B(BTN_B,40);
bool in_loop=false;

char* _version_ = "Version 2.1 5/Mar/21";
int dest = 1;
int delta_T = 100;
int delta_offset = 25;
int delta_adjusted;
float threshold = 1.2;
int scale = 10;
bool start_read = false;

float accX;
float accY;
float accZ;
float gyroX;
float gyroY;
float gyroZ;
float acc_buff[21000];
int buf_size = sizeof(acc_buff);

long idx=0;
bool folded = false;
long seqno = 0;
unsigned long mils_initial=0;
unsigned long mils = 0;
float secs = 0.0;

void acc_read(void);
void Display_readings(float X,float Y,float Z);
void on_B_Pressed();
void on_A_Pressed();


void Display_readings(float X,float Y,float Z,float gX,float gY,float gZ,float secs){
  M5.Lcd.setCursor(40,30);
  M5.Lcd.printf("%+6.2f  ",X );
  M5.Lcd.setCursor(140,30);
  M5.Lcd.printf("%+6.2f  ",gX);
  
  M5.Lcd.setCursor(40,50);
  M5.Lcd.printf("%+6.2f  ",Y );
  M5.Lcd.setCursor(140,50);
  M5.Lcd.printf("%+6.2f  ",gY);
  M5.Lcd.setCursor(40,70);
  M5.Lcd.printf("%+6.2f  ",Z );
  M5.Lcd.setCursor(140,70);
  M5.Lcd.printf("%+6.2f  ",gZ);
  M5.Lcd.setCursor(70,90);
  M5.Lcd.printf("%6.3f",secs);
}

void audio_beep() {
    M5.Beep.tone(4000);
    delay(100);
    M5.Beep.mute();
    delay(100);
}

void on_A_Pressed() {
  if (in_loop) {
    Serial.println("Button A has been pressed! Toggle read");
    start_read = !start_read;
  }
}


void on_A_pressedFor(){
    Serial.println("Restarting device...");
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(40,30);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Restarting");
    audio_beep();
    ESP.restart();
  }

void on_B_Pressed() {
  int seqno = 0;
  start_read = false;
  int upto=0;

  Serial.print("Size of Buff ");
  Serial.println(sizeof(acc_buff));
  Serial.print("folded? ");
  Serial.println(folded);
  Serial.print("idx ");
  Serial.println(idx);
  
  if (folded) {
    upto = buf_size/4;
  } else {
    upto = idx ;
  }

  

  sprintf(message,"{\"Version\":\"%s\",\"Device\":\"%s\",\"period(ms)\":%d}\n",_version_,blename.c_str(),delta_T);
 
  dumpBLE(message);
  Serial.print(message);
  
  sprintf(message,"%s\n","Secs,AccX,AccY,AccZ,GyroX,GyroY,GyroZ");
  dumpBLE(message);
  Serial.print(message);
  for (int i=0;i<upto;i=i+7) {
    seqno = (int) acc_buff[i];
    sprintf(message,"%6.3f, %+6.2f, %+6.2f, %+6.2f, %+6.2f, %+6.2f, %+6.2f\n",
        acc_buff[i],
        acc_buff[i+1]*scale,acc_buff[i+2]*scale,acc_buff[i+3]*scale,
        acc_buff[i+4],acc_buff[i+5],acc_buff[i+6]);
    dumpBLE(message);
    
    Serial.print(message);
    
  
      delay(10);  
    }
}


#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("BLE Connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("BLE Disconnected");
    }
};


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      std::string cmd;
      std::string argstr;
      
      cmd = rxValue.substr(0,1);
      argstr = rxValue.substr(1,3);
      
      if(cmd == "a"){
        M5.Lcd.fillScreen(RED);
      }
      if(cmd == "b"){
        int r = rand() % sizeof(COLORS_LIST);
        M5.Lcd.fillScreen(COLORS_LIST[r]);
      }
      if(cmd == "c"){
        if(colori < sizeof(COLORS_LIST)){
          M5.Lcd.fillScreen(COLORS_LIST[colori]);
          colori++;
        }else{
          colori = 0;
          M5.Lcd.fillScreen(COLORS_LIST[colori]);
        }
      }
      if(cmd == "r"){
        M5.Lcd.fillScreen(BLACK);
      }
      
      
    }
};
void setup() {
  
  Serial.println("Waiting for a client connection to send Acc data...");
  Serial.begin(115200);
  Button_A.begin();
  Button_B.begin();

  Button_A.onPressed(on_A_Pressed);
  Button_B.onPressed(on_B_Pressed);
  Button_A.onPressedFor(2000,on_A_pressedFor);

  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 5);
  
  uint64_t chipid = ESP.getEfuseMac();
  blename = "FLY "+String((uint32_t)(chipid>>32),HEX);
  

  BLEDevice::init(blename.c_str());
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  char buffer[100];
  pServer->getAdvertising()->start();
}

void dumpBLE(char* msg) {
  if (deviceConnected) {
        pTxCharacteristic->setValue((uint8_t*)msg, strlen(msg));
        pTxCharacteristic->notify();
  }
}

void loop() {
  in_loop=true;
  Button_A.read();
  Button_B.read();
  delay(500);
  secs += 0.1;


  if (!deviceConnected && oldDeviceConnected) {
        delay(500);
        secs += 0.5;
        pServer->startAdvertising();
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
  }
  if (deviceConnected && !oldDeviceConnected) {
      oldDeviceConnected = deviceConnected;
  }
  if(secs % 10.0 == 0){
    char convert[16];
    sprintf(convert, "%.3f secs", secs);
    dumpBLE(convert);
  }
}
