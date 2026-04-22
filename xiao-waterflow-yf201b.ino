#define FLOW_PIN       7   // D5
#define INTERVAL_MS    5000
// YF-201B: F(Hz) = 7.5 * Q(L/min)  →  450 pulsen per liter
#define PULSES_PER_LITER 450.0f

volatile uint32_t pulseCount = 0;

float totalLiters  = 0.0f;
uint32_t lastTime  = 0;

void IRAM_ATTR onPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(FLOW_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), onPulse, FALLING);
  lastTime = millis();
}

void loop() {
  if (millis() - lastTime >= INTERVAL_MS) {
    noInterrupts();
    uint32_t count = pulseCount;
    pulseCount = 0;
    interrupts();

    float intervalMin = INTERVAL_MS / 60000.0f;
    float flowRate    = (count / PULSES_PER_LITER) / intervalMin;
    totalLiters      += count / PULSES_PER_LITER;

    Serial.printf("Flow: %.2f L/min | Totaal: %.2f L\n", flowRate, totalLiters);

    lastTime = millis();
  }
}
