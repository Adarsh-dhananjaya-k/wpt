/*!
 *@file       : IoT Car Parking System with Blynk Durian UNO.ino
 *@copyright  : Copyright (c) 2023 MYBOTIC (http://www.mybotic.com.my)
 *@licence    : The MIT License (MIT)
 *@author     : Nurfarah Nazuwah
 *@version    : V2.0
 *@date       : 17-07-2023
 *
*/

// #define BLYNK_TEMPLATE_ID "TMPL6ldP7yjEZ"
// #define BLYNK_TEMPLATE_NAME "IoT Car Parking System with Blynk Durian UNO"
// #define BLYNK_AUTH_TOKEN "NYsrJqHEp3wyb-GzacJH-b82e3hOaPyU"


#define BLYNK_TEMPLATE_ID "TMPL3S0lbbPDz"
#define BLYNK_TEMPLATE_NAME "Smart Parking System"
#define BLYNK_AUTH_TOKEN "NYsrJqHEp3wyb-GzacJH-b82e3hOaPyU"

#include "DurianBlynkESP8266.h"

//comment this if using Serial for ESP
// or Software Serial on Uno, Nano...
// #include <SoftwareSerial.h>
// SoftwareSerial EspSerial(2, 3); // RX, TX

//uncomment this if using Serial for ESP
//#define EspSerial Serial

#define ESP8266_BAUD 9600

char auth[] = BLYNK_AUTH_TOKEN;

#ifdef BLYNK_TEMPLATE_ID && BLYNK_TEMPLATE_NAME
char tempID[] = BLYNK_TEMPLATE_ID; 
char deviceName[] = BLYNK_TEMPLATE_NAME; 
#else
char tempID[5]; 
char deviceName[5]; 
#endif

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "INNOVATION HUB";
char pass[] = "prsc$123";

//esp8266 serial
DBlynk DBlynk(&EspSerial);

#include <Servo.h> //includes the servo library
#include <Wire.h> 
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27, 20, 4);

// Servo Servo_Gate;

#define CAR_SLOT 2

#define SERVO_PIN  11
#define GATE_CLOSE 0
#define GATE_OPEN 90

#define IR_ENTER 9
#define IR_BACK  10

#define IR_CAR1 16
#define IR_CAR2 4
#define IR_CAR3 A2
#define IR_CAR4 A3
#define IR_CAR5 7
#define IR_CAR6 8

#define BUZZER  4
#define LED     13

// Define Virtual Pin Blynk
#define V_LED_S1  V0
#define V_LED_S2  V1
#define V_LED_S3  V2
#define V_LED_S4  V3
#define V_LED_S5  V4
#define V_LED_S6  V5
#define V_CAR_SLOT V2

#define BLYNK_GREEN  "#23C48E"
#define BLYNK_RED    "#D3435C"

short gsArray_Sensor[CAR_SLOT] = {IR_CAR1, IR_CAR2} ; //, IR_CAR3, IR_CAR4, IR_CAR5, IR_CAR6};
short garraysV_Sensor[CAR_SLOT] = {V_LED_S1, V_LED_S2}; //, V_LED_S3,V_LED_S4,V_LED_S5,V_LED_S6};

unsigned long gulStart_LCD_Timer = 0;
unsigned long gulStart_Upload_Timer = 0;

void setup()
{
  Serial.begin(9600);

  // Servo_Gate.attach(SERVO_PIN);
  // Servo_Gate.write(GATE_CLOSE);
  delay(500);
  // Servo_Gate.detach();

  // lcd.init();
  // lcd.backlight();
  // lcd.print("Wifi Connect...");

  // pinMode(BUZZER, OUTPUT);
  // tone(BUZZER, 1000);
  // delay(300);
  // tone(BUZZER, 500);
  // delay(300);
  // noTone(BUZZER);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  //Connect to Blynk
  DBlynk.begin(tempID, deviceName, auth, ssid, pass);

  tone(BUZZER, 500);
  delay(300);
  tone(BUZZER, 1000);
  delay(300);
  noTone(BUZZER);

  // lcd.setCursor(0,1);
  // lcd.print("Done!");

  pinMode(IR_CAR1, INPUT_PULLUP);
  pinMode(IR_CAR2, INPUT_PULLUP);
  pinMode(IR_CAR3, INPUT_PULLUP);
  pinMode(IR_CAR4, INPUT_PULLUP);
  pinMode(IR_CAR5, INPUT_PULLUP);
  pinMode(IR_CAR6, INPUT_PULLUP);
  
  pinMode(IR_ENTER, INPUT_PULLUP);
  pinMode(IR_BACK, INPUT_PULLUP);
      
  //lcd.backlight();  
  //lcd.begin(20, 4);  
  //lcd.setCursor(0,1);
  //lcd.print(" IoT Smart Parking  ");
  //lcd.setCursor (0,2);
  //lcd.print("  System w/ Blynk   ");
  delay(2000);  

  for(short i=0; i<CAR_SLOT; i++)
  {
    DBlynk.virtualWrite(garraysV_Sensor[i], 1);
    DBlynk.setProperty(garraysV_Sensor[i], "color", BLYNK_GREEN);
  }
  
  DBlynk.virtualWrite(V_CAR_SLOT, CAR_SLOT);
  
  gulStart_LCD_Timer = millis();
}

void loop()
{
  unsigned short usSensorStatus[CAR_SLOT] = {0,0,0,0,0,0};
  short sCar_Slot = CAR_SLOT;

  DBlynk.run();

  if((sIR_Detect(IR_ENTER) == 1) || (sIR_Detect(IR_BACK) == 1))
  {
    Servo_Gate.attach(SERVO_PIN);
    Servo_Gate.write(GATE_OPEN);
    delay(2000);
    Servo_Gate.write(GATE_CLOSE);
    delay(500);
    Servo_Gate.detach();
  }

  if(millis() - gulStart_Upload_Timer > 1000)
  {
    for(short i=0; i<CAR_SLOT; i++)
    {
      usSensorStatus[i]= sIR_Detect(gsArray_Sensor[i]);

      if(usSensorStatus[i] == 1)
      {
        sCar_Slot--;
        DBlynk.setProperty(garraysV_Sensor[i], "color", BLYNK_RED);
      }
      else 
      {
        DBlynk.setProperty(garraysV_Sensor[i], "color", BLYNK_GREEN);
      }
    }

    //Serial.print("sCar_Slot: ");
    //Serial.println(sCar_Slot);

    DBlynk.virtualWrite(V_CAR_SLOT, sCar_Slot);

    // vLCD_Display(sCar_Slot, usSensorStatus);
  }
}

void vLCD_Display(short sCar_Slot ,short sArray_Sensor[])
{
  //lcd.clear();
  //lcd.print("Car Slot Left: ");
  //lcd.print(sCar_Slot);

  //lcd.setCursor(0,1);
  //lcd.print("S1: ");
  if(sArray_Sensor[0] == 1)
  {
    //lcd.print("Fill");
  }
  else
  {
    //lcd.print("Empty");
  }
  
  //lcd.setCursor(0,2);
  //lcd.print("S2: ");
  if(sArray_Sensor[1] == 1)
  {
    //lcd.print("Fill");
  }
  else
  {
    //lcd.print("Empty");
  }

  //lcd.setCursor(0,3);
  //lcd.print("S3: ");
  if(sArray_Sensor[2] == 1)
  {
    //lcd.print("Fill");
  }
  else
  {
    //lcd.print("Empty");
  }

  //lcd.setCursor(10,1);
  //lcd.print("S4: ");
  if(sArray_Sensor[3] == 1)
  {
    //lcd.print("Fill");
  }
  else
  {
    //lcd.print("Empty");
  }

  //lcd.setCursor(10,2);
  //lcd.print("S5: ");
  if(sArray_Sensor[4] == 1)
  {
    //lcd.print("Fill");
  }
  else
  {
    //lcd.print("Empty");
  }

  //lcd.setCursor(10,3);
  //lcd.print("S6: ");
  if(sArray_Sensor[5] == 1)
  {
    //lcd.print("Fill");
  }
  else
  {
    //lcd.print("Empty");
  }
  
}

unsigned short sIR_Detect(short sWhichSensor)
{
  if(digitalRead(sWhichSensor) == 0)
  {
    delay(50);
    if(digitalRead(sWhichSensor) == 0)
    {
      return 1; 
    }
    else
    {
      return 0;
    }
  }
  else 
  {
    return 0; 
  }
}
