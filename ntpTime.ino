#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   D7  // or SCK
#define DATA_PIN  D5  // or MOSI
#define CS_PIN    D4  // or SS

MD_MAX72XX Display = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

unsigned char setzero[8]={0x1C, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x1C}; //Digit 0
unsigned char setone[8]={0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C};  //Digit 1
unsigned char settwo[8]={0x1C, 0x36, 0x30, 0x30, 0x1C, 0x6, 0x36, 0x3E};   //Digit 2
unsigned char setthree[8]={0x1C, 0x36, 0x30, 0x3C, 0x30, 0x30, 0x36, 0x1C};//Digit 3
unsigned char setfour[8]={0x30, 0x38, 0x34, 0x36, 0x3E, 0x30, 0x30, 0x30}; //Digit 4
unsigned char setfive[8]={0x3E, 0x6, 0x6, 0x1E, 0x30, 0x30, 0x36, 0x1E};   //Digit 5
unsigned char setsix[8]={0x1C, 0x36, 0x6, 0x1E, 0x36, 0x36, 0x36, 0x1C};   //Digit 6
unsigned char setseven[8]={0x3E, 0x3E, 0x30, 0x18, 0xC, 0x6, 0x6, 0x6};    //Digit 7
unsigned char seteight[8]={0x1C, 0x36, 0x36, 0x1C, 0x36, 0x36, 0x36, 0x1C};//Digit 8
unsigned char setnine[8]={0x1C, 0x36, 0x36, 0x3C, 0x30, 0x30, 0x32, 0x1C}; //Digit 9
unsigned char setdots = 0x24;
unsigned char setblank = 0x0;

String Time, hour, minute, second;
String Formatted_time;

const char *ssid     = "";
const char *password = "";
int digitIndex = 0;
String digit0 = "61";
String digit1 = "61";
String digit2 = "61";
String digit3 = "61";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.mx.pool.ntp.org", -21600, 43200);

void obtainTime() {
  Formatted_time = timeClient.getFormattedTime();

  hour = Formatted_time.substring(0, 2);
  minute = Formatted_time.substring(3, 5);

  if ((hour.toInt() == 0) or (hour.toInt() == 12)) {
    hour = String(12);
  }
  else {
    hour = String(hour.toInt() % 12);
    if (hour.length() == 1) {
      hour = "0" + hour;
    }
  }
  Serial.println ( hour + ":" + minute + "  " + Formatted_time);
}

void setNumber(String Sdigit,int digitIndex) {
  int digit = Sdigit.toInt();
  switch (digit) {
    case 0:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setzero[j]);
      } 
      break;
    case 1:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setone[j]);
      }
      break;
    case 2:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, settwo[j]);
      }
      break;
    case 3:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setthree[j]);
      }
      break;
    case 4:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setfour[j]);
      }
      break;
    case 5:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setfive[j]);
      }
      break;
    case 6:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setsix[j]);
      }
      break;
    case 7:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setseven[j]);
      }
      break;
    case 8:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, seteight[j]);
      }
      break;
    case 9:
      for (int j=0; j<8; j++) {
        Display.setRow(digitIndex, j, setnine[j]);
      }
      break;
  }
}

void setup(){
  Serial.begin(115200);
  Serial.println ("Starting...");
  WiFi.begin(ssid, password);
  
  Display.begin();
  Display.clear();
  
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Display.setColumn(1, 7, setdots);
    delay ( 500 );
    Display.setColumn(1, 7, setblank);
  }

  Display.control(MD_MAX72XX::INTENSITY , 0);

  timeClient.begin();
  timeClient.update();
}

void loop() {
  obtainTime();

  if (digit0 != hour.substring(0, 1) && hour.substring(0, 1) != "0"){
    digit0 = hour.substring(0, 1);
    digitIndex = 0;
    setNumber(digit0, digitIndex);
  } else if (digit0 == "0") {
    Display.clear(0);
  }
  if (digit1 != hour.substring(1, 2)){
    digit1 = hour.substring(1, 2);
    digitIndex = 1;
    setNumber(digit1, digitIndex);
  }
  if (digit2 != minute.substring(0, 1)){
    digit2 = minute.substring(0, 1);
    digitIndex = 2;
    setNumber(digit2, digitIndex);
  }
  if (digit3 != minute.substring(1, 2)){
    digit3 = minute.substring(1, 2);
    digitIndex = 3;
    setNumber(digit3, digitIndex);
  }
  
  Display.setColumn(1, 7, setdots);
  delay(500);
  Display.setColumn(1, 7, setblank);
  delay(500);
}