#define BLYNK_TEMPLATE_ID   "TMPL3S0lbbPDz"
#define BLYNK_TEMPLATE_NAME "Smart Parking System"
#define BLYNK_AUTH_TOKEN    "NYsrJqHEp3wyb-GzacJH-b82e3hOaPyU"


#define BLYNK_TEMPLATE_ID "TMPL3kEUEI9n5"
#define BLYNK_TEMPLATE_NAME "parking system"
#define BLYNK_AUTH_TOKEN "Zg96o9yMTbAS9_eRXw4TPeoH2geVgnM7"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "INNOVATION HUB";
char pass[] = "prsc$123";

// --- IR sensor pins ---
#define IR1_PIN D2  
#define IR2_PIN D3  

BlynkTimer timer;

// Function to check parking slots
void checkSlots() {
  int ir1 = digitalRead(IR1_PIN);
  int ir2 = digitalRead(IR2_PIN);

  int freeSlots = 0;

  // --- Slot 1 ---
  if (ir1 == LOW) {
    // Occupied
    Blynk.virtualWrite(V0, 255);
    Blynk.setProperty(V0, "color", "#FF0000"); // Red
    Serial.println("Slot 1: Occupied");
  } else {
    // Free
    Blynk.virtualWrite(V0, 255);
    Blynk.setProperty(V0, "color", "#00FF00"); // Green
    freeSlots++;
    Serial.println("Slot 1: Free");
  }

  // --- Slot 2 ---
  if (ir2 == LOW) {
    // Occupied
    Blynk.virtualWrite(V1, 255);
    Blynk.setProperty(V1, "color", "#FF0000"); // Red
    Serial.println("Slot 2: Occupied");
  } else {
    // Free
    Blynk.virtualWrite(V1, 255);
    Blynk.setProperty(V1, "color", "#00FF00"); // Green
    freeSlots++;
    Serial.println("Slot 2: Free");
  }

  // Update number of free slots on V2
  Blynk.virtualWrite(V2, freeSlots);
  Serial.print("Available slots: ");
  Serial.println(freeSlots);
}

void setup() {
  Serial.begin(115200);
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Check slots every 1 second
  timer.setInterval(1000L, checkSlots);
}

void loop() {
  Blynk.run();
  timer.run();
}

