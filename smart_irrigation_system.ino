#define BLYNK_TEMPLATE_ID "TMPL3hrc7zM-v"
#define BLYNK_TEMPLATE_NAME "irrigation system"
#define BLYNK_AUTH_TOKEN "j7IL1zM_Tzpdj71nOODb28WemjpZ-xVo"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "INNOVATION HUB";
char pass[] = "prsc$123";

// === Soil Moisture Sensor ===
#define SOIL_PIN A0   // ONLY analog pin on ESP8266

// === Relay (Water Pump) ===
#define RELAY_PIN D5
int relayState = 0;   // 0 = OFF, 1 = ON
int manualMode = 0;   // 0 = Auto, 1 = Manual ON

// === DHT11 Sensor ===
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// === Read Soil Moisture ===
void readSoil() {
  int sensorValue = analogRead(SOIL_PIN);  // 0–1023
  int moisturePercent = map(sensorValue, 1023, 0, 0, 100);

  // Send moisture % to Blynk Gauge (V0)
  Blynk.virtualWrite(V0, moisturePercent);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Auto control only if manual switch is OFF
  if (manualMode == 0) {
    if (moisturePercent < 40 && relayState == 0) {
      digitalWrite(RELAY_PIN, HIGH);
      relayState = 1;
      Blynk.virtualWrite(V3, 1);  // Update switch in app
      Serial.println("Soil dry → Pump ON (Auto)");
    } 
    else if (moisturePercent > 60 && relayState == 1) {
      digitalWrite(RELAY_PIN, LOW);
      relayState = 0;
      Blynk.virtualWrite(V3, 0);
      Serial.println("Soil wet → Pump OFF (Auto)");
    }
  }
}

// === Read DHT11 ===
void readDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // °C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send to Blynk
  Blynk.virtualWrite(V1, t); // Temperature
  Blynk.virtualWrite(V2, h); // Humidity

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C | Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

// === Manual Relay Control (Switch V3) ===
BLYNK_WRITE(V3) {
  int state = param.asInt();

  if (state == 1) {
    manualMode = 1;        // Manual override
    relayState = 1;
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Pump ON (Manual)");
  } else {
    manualMode = 0;        // Return to auto mode
    relayState = 0;
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Pump OFF (Switch OFF → Auto resumes)");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Run tasks every 5 sec
  timer.setInterval(5000L, readSoil);
  timer.setInterval(5000L, readDHT);
}

void loop() {
  Blynk.run();
  timer.run();
}
