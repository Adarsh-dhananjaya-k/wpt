#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// ====== WiFi Credentials ======
const char* ssid = "INNOVATION HUB";
const char* pass = "prsc$123";

// ====== SinricPro Credentials ======
#define APP_KEY    "eb09e6cb-3e01-4711-a3e1-ff65e3d31a3f"     // From SinricPro dashboard
#define APP_SECRET "b5177e7d-169a-43ee-b1c1-6bedcef74812-79739b36-49b3-45f7-9dd9-9d39cbc51172"  // From SinricPro dashboard

// ====== Device IDs ======
  
// #define SWITCH_ID         "68c2a89f3fdc49efb6a659ea"
#define RELAY1_ID "68ccf1f8b73c366187ef49ea"  // Create a "Switch" in SinricPro
#define RELAY2_ID "68ccf19dc6e94834159ae5fd"  // Create a second "Switch"

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




