#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// ====== WiFi Credentials ======
const char* ssid = "INNOVATION HUB";
const char* password = "prsc$123";

// ====== DHT Sensor ======
#define DHTPIN D4      // GPIO2 on NodeMCU
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ====== WebServer ======
ESP8266WebServer server(80);

void handleRoot() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>DHT11 Monitor</title>";
  html += "<style>";
  html += "body { font-family: Arial; text-align:center; background:#f4f4f4; }";
  html += "h1 { color:#333; }";
  html += ".card { display:inline-block; background:white; padding:20px; margin:20px; border-radius:10px; box-shadow:0 4px 6px rgba(0,0,0,0.1); }";
  html += ".value { font-size:2em; margin:10px 0; color:#0077cc; }";
  html += "</style></head>";
  html += "<body>";
  html += "<h1>🌡️ IoT DHT11 Sensor</h1>";
  html += "<div class='card'><h2>Temperature</h2><div class='value'>" + String(t) + " &deg;C</div></div>";
  html += "<div class='card'><h2>Humidity</h2><div class='value'>" + String(h) + " %</div></div>";
  html += "<p>Last updated: " + String(millis()/1000) + "s since start</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
