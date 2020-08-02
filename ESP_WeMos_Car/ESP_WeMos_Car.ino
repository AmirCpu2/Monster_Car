#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include "Virtuino_ESP_WifiServer.h"

const char* ssid = "Irancell-TD-B5142-2858_1";    
const char* password = "P@ssM0rd";
int port = 8000;
WiFiServer server(port);      // Server port


Virtuino_ESP_WifiServer virtuino(&server);

//WeMos ESP8266 pins= D0,D1,D2,D3,D4,D5,D6,D7,D8
int d0=16, d1=5, d2=4, d3=0, d4=2, d5=14, d6=12, d7=13, d8=15;

// Example variables
int MaxVDPin=8;
int counter =0;
long storedTime=0;

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  //----- Virtuino settings
  virtuino.DEBUG=true;                         // set this value TRUE to enable the serial monitor status
  virtuino.password="1234";                    // Set a password to your web server for more protection 
                                               // avoid special characters like ! $ = @ # % & * on your password. Use only numbers or text characters

  Serial.begin(9600);                          // Enable this line only if DEBUG=true
  delay(10);
  
  //----  1. Settings as Station - Connect to a WiFi network
  Serial.println("Connecting to "+String(ssid));
  
  WiFi.mode(WIFI_STA);                       // Config module as station only.
  WiFi.begin(ssid, password);
  /*----------------- Display Initialize -------------------*/
  OLED.begin();
  OLED.clearDisplay();

  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.println("Please set Hotspot");
  OLED.print("SSID: ");
  OLED.println(ssid);
  OLED.print("PASSWORD: ");
  OLED.println(password);
  OLED.display(); //output 'display buffer' to screen  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  /*--------------------  Connected  WIFI  ----------------------*/
  OLED.clearDisplay();

  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.println("is connected.. :)");
  OLED.println("Please set App");
  OLED.print("IP: ");
  OLED.println(WiFi.localIP());
  Serial.println(WiFi.localIP());
  OLED.print("PORT: ");
  OLED.println(port);
  OLED.println("key: 123");
  
  OLED.display(); //output 'display buffer' to screen
  
  delay(1000); //delay
  
  // ---- Start the server
  server.begin();
  
  //---- Start Status App
  virtuino.vDigitalMemoryWrite(0,1);
  //virtuino.vMemoryWrite(2,random(1000));
  
  //---- Enter your setup code below
  //  
  //    pinMode(d1, OUTPUT);//LCD
  //    pinMode(d2, OUTPUT);//LCD

  /*------------------SerialControl--------------------
   * F:LED Front {0,1}=> F1,F0
   * H:LED HeadLight {0,1,2}=> H2,H1,H0
   * S:LED Stop (Back) {0,1}=> S1,S0
   * B:Beep Speeker Beep {0,1}=> B1,B0
  --------------------SerialControl-------------------*/
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);//Motor 2 => Right
  pinMode(d6, OUTPUT);//Motor 2 => Left
  pinMode(d7, OUTPUT);//Motor 1 => Front
  pinMode(d8, OUTPUT);//Motor 1 => Back

}

char vPin[] = {'O',7,8,5,6,'F','D'/*Dereft*/,'H','K'/*H2*/};
int TempState[] = {0,0,0,0,0,0,0,0,0};
void loop() {
//  Yes LetsGOOO ^__*
  virtuino.run();
/*------------------  Requst Conterol --------------------*/
  for(int i=1;i<=MaxVDPin;i++)
  {
    int v = virtuino.vDigitalMemoryRead(i);              // Read virtual memory 0 to n from Virtuino app
                 
    //Serial.println("-------Virtual pin DV"+String(i)+" is changed to="+String(v));

    //Check Last vs new status
    if(TempState[i] != v)
    {
      switch(vPin[i])
      {
        case(5):
          digitalWrite(d5,v);
          digitalWrite(d6,0);
          break;
        case(6):
          digitalWrite(d6,v);
          digitalWrite(d5,0);
          break;
        case(7):
          digitalWrite(d7,v);
          digitalWrite(d8,0);
          break;
        case(8):
          digitalWrite(d8,v);
          digitalWrite(d7,0);
          break;
        case('F'):
          Serial.print("F");
          Serial.println(v);
          break;
        case('D'):
          Serial.print("D");
          Serial.println(v);
          break;
        case('H'):
          Serial.print("H");
          Serial.println(v);
          break;
        case('K'):
          if(v>0)
          {
            Serial.println("H2");
          }
          else
          {
            Serial.println("H0");
          }
          break;
      }
  
      //Set Last status
      TempState[i] = v;
    }
      
  }

}
