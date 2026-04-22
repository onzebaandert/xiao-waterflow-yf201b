# YF-201B Waterflow sensor op XIAO ESP32-C3

## Doel
Pulsen tellen, flow rate berekenen in L/min, totaal volume in Liter.

## Hardware
- **Board:** Seeed XIAO ESP32-C3
- **Sensor:** YF-201B waterflow sensor
- **Signaalpin:** GPIO7 (D5)

## Staat van het project
- [x] Repo gekloond
- [x] CLAUDE.md aangemaakt
- [x] Sketch schrijven
- [x] Compileren
- [x] Flashen
- [x] Testen — werkende sketch op GPIO7 (D5), getest en gepusht

## Volgende stap
Integratie in LoRa systeem.

## Toekomst
Verder uitbreiden met dataopslag, grafieken of MQTT.

## Notities
- WiFi Access Point werkend: XIAO maakt netwerk "WaterMeter" aan (wachtwoord: water123)
- Webpagina bereikbaar op http://192.168.4.1, ververst elke 5 seconden
- Android tip: zet "automatisch opnieuw verbinden" uit voor mobiele data, anders valt Android terug op 4G en is de pagina niet bereikbaar
