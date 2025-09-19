#define BLYNK_TEMPLATE_ID "TMPL3XgLcQirg"
#define BLYNK_TEMPLATE_NAME "icc"
#define BLYNK_AUTH_TOKEN "VWXrh5rgpgY2mk_uIXBHFnyUwHOk2g6C"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "INNOVATION HUB";
char pass[] = "prsc$123";

// === Soil Moisture Sensor ===
#define SOIL_PIN A0   // Analog pin (0–1V only on ESP8266!)

// === Relay ===
#define RELAY_PIN D1
int relayState = 0;

// === DHT11 Sensor ===
#define DHTPIN D0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// === Read Soil Moisture ===
void readSoil() {
  int sensorValue = analogRead(SOIL_PIN);  // 0–1023
  int moisturePercent = map(sensorValue, 1023, 0, 0, 100);
  // Dry ~1023, Wet ~0
  Blynk.virtualWrite(V0, moisturePercent);
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");
  // if 
}

// === Read DHT11 ===
void readDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // °C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t); // Temperature
  Blynk.virtualWrite(V2, h); // Humidity

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C | Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

// === Manual Relay Control (Switch V1) ===
BLYNK_WRITE(V3) {
  relayState = param.asInt();
  Serial.print(relayState);
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  Serial.print("Relay state: ");
  Serial.println(relayState ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // // Run tasks every 5 sec
  // timer.setInterval(5000L, readSoil);
  // timer.setInterval(5000L, readDHT);
}

void loop() {
  // readSoil();
  // readDHT();
  Blynk.run();
  timer.run();
}

