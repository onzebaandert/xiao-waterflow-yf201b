#include <WiFi.h>
#include <WebServer.h>

#define FLOW_PIN         7    // D5
#define INTERVAL_MS      5000
// YF-201B: F(Hz) = 7.5 * Q(L/min)  →  450 pulsen per liter
#define PULSES_PER_LITER 450.0f

const char* ssid     = "WaterMeter";
const char* password = "water123";

volatile uint32_t pulseCount = 0;
float totalLiters  = 0.0f;
float flowRate     = 0.0f;
uint32_t lastTime  = 0;

WebServer server(80);

void IRAM_ATTR onPulse() {
  pulseCount++;
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>"
    "<meta charset='UTF-8'>"
    "<meta http-equiv='refresh' content='5'>"
    "<title>Waterflow</title>"
    "<style>"
    "body{font-family:sans-serif;text-align:center;padding:2em;background:#f0f4f8}"
    "h1{color:#2c3e50}div.card{display:inline-block;margin:1em;padding:1.5em 2.5em;"
    "background:#fff;border-radius:12px;box-shadow:0 2px 8px rgba(0,0,0,.15)}"
    ".val{font-size:2.5em;font-weight:bold;color:#2980b9}"
    ".lbl{color:#7f8c8d;margin-top:.3em}"
    "</style></head><body>"
    "<h1>YF-201B Waterflow</h1>"
    "<div class='card'><div class='val'>" + String(flowRate, 2) + " L/min</div>"
    "<div class='lbl'>Flow</div></div>"
    "<div class='card'><div class='val'>" + String(totalLiters, 2) + " L</div>"
    "<div class='lbl'>Totaal</div></div>"
    "<p style='color:#aaa;font-size:.8em'>Pagina ververst elke 5 seconden</p>"
    "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(FLOW_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), onPulse, FALLING);
  lastTime = millis();

  WiFi.softAP(ssid, password);
  Serial.print("Access Point gestart: ");
  Serial.println(ssid);
  Serial.print("IP-adres: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Webserver gestart op poort 80");
}

void loop() {
  server.handleClient();

  if (millis() - lastTime >= INTERVAL_MS) {
    noInterrupts();
    uint32_t count = pulseCount;
    pulseCount = 0;
    interrupts();

    float intervalMin = INTERVAL_MS / 60000.0f;
    flowRate    = (count / PULSES_PER_LITER) / intervalMin;
    totalLiters += count / PULSES_PER_LITER;

    Serial.printf("Flow: %.2f L/min | Totaal: %.2f L\n", flowRate, totalLiters);

    lastTime = millis();
  }
}
