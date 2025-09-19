#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ====== WiFi Credentials ======
const char* ssid = "INNOVATION HUB";
const char* password = "prsc$123";

// ====== Ultrasonic Sensor Pins ======
#define TRIG_PIN D5
#define ECHO_PIN D6

// ====== Tank Dimensions ======
const int tankHeight = 30;   // Tank depth in cm

// ====== Web Server ======
ESP8266WebServer server(80);

long readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;  // in cm
  return distance;
}

int getWaterLevel() {
  long distance = readUltrasonic();
  int level = tankHeight - distance;
  if (level < 0) level = 0;
  if (level > tankHeight) level = tankHeight;

  int percent = map(level, 0, tankHeight, 0, 100);
  return percent;
}

// === Webpage ===
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Water Level</title>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f0f8ff;}";
  html += "h1{color:#0066cc;}";
  html += ".container{width:80%;margin:auto;}";
  html += ".bar{width:100%;background:#ddd;border-radius:25px;overflow:hidden;height:40px;}";
  html += ".fill{height:40px;width:0;background:#00bfff;text-align:center;line-height:40px;color:white;font-weight:bold;}";
  html += "</style>";
  html += "<script>";
  html += "function updateData(){fetch('/data').then(r=>r.text()).then(level=>{";
  html += "document.getElementById('level').innerText=level+'%';";
  html += "document.getElementById('fill').style.width=level+'%';";
  html += "document.getElementById('fill').innerText=level+'%';";
  html += "});}";
  html += "setInterval(updateData,1000);";
  html += "</script></head><body onload='updateData()'>";
  html += "<div class='container'>";
  html += "<h1>IoT Water Level Indicator</h1>";
  html += "<p>Current Water Level:</p>";
  html += "<h2 id='level'>0%</h2>";
  html += "<div class='bar'><div class='fill' id='fill'>0%</div></div>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}

// === AJAX Data Endpoint ===
void handleData() {
  int waterLevel = getWaterLevel();
  server.send(200, "text/plain", String(waterLevel));
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}
