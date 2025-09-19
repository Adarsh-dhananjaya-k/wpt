#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// ====== WiFi Credentials ======
const char* ssid = "INNOVATION HUB";
const char* pass = "prsc$123";

// ====== SinricPro Credentials ======
#define APP_KEY    "664a1085-f119-4533-adf3-0d283f6843d7"     // From SinricPro dashboard
#define APP_SECRET "3665e088-24f5-447b-b897-8e48b35fb258-28514f4a-e0c2-449d-977d-ca1e8264f14c"  // From SinricPro dashboard

// ====== Device IDs ======

#define APP_KEY           "664a1085-f119-4533-adf3-0d283f6843d7"      
#define APP_SECRET        "3665e088-24f5-447b-b897-8e48b35fb258-28514f4a-e0c2-449d-977d-ca1e8264f14c"   
// #define SWITCH_ID         "68c2a89f3fdc49efb6a659ea"
#define RELAY1_ID "68c2a89f3fdc49efb6a659ea"  // Create a "Switch" in SinricPro
#define RELAY2_ID "68c2aa69690df731215c976f"  // Create a second "Switch"

// ====== Relay Pins ======
#define RELAY1_PIN D5
#define RELAY2_PIN D6

bool relay1State = false;
bool relay2State = false;

// ====== Callback for Relay 1 ======
bool onPowerState1(const String &deviceId, bool &state) {
  if (deviceId == RELAY1_ID) {
    relay1State = state;
    digitalWrite(RELAY1_PIN, relay1State ? HIGH : LOW);
    Serial.printf("Relay 1 (Pump/Light) %s via Alexa\n", relay1State ? "ON" : "OFF");
  }
  return true;
}

// ====== Callback for Relay 2 ======
bool onPowerState2(const String &deviceId, bool &state) {
  if (deviceId == RELAY2_ID) {
    relay2State = state;
    digitalWrite(RELAY2_PIN, relay2State ? HIGH : LOW);
    Serial.printf("Relay 2 (Pump/Light) %s via Alexa\n", relay2State ? "ON" : "OFF");
  }
  return true;
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);

  // WiFi
  WiFi.begin(ssid, pass);
  Serial.printf("Connecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // SinricPro setup
  SinricProSwitch& mySwitch1 = SinricPro[RELAY1_ID];
  mySwitch1.onPowerState(onPowerState1);

  SinricProSwitch& mySwitch2 = SinricPro[RELAY2_ID];
  mySwitch2.onPowerState(onPowerState2);

  SinricPro.onConnected([](){ Serial.println("Connected to SinricPro"); });
  SinricPro.onDisconnected([](){ Serial.println("Disconnected from SinricPro"); });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}



