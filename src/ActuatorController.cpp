#include "ActuatorController.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
DataCollector dataCollector = DataCollector();
Actuator* actuators[] = {
    new Actuator(D1, 1, &settings.getSettings()->actuator1),
    new Actuator(D2, 2, &settings.getSettings()->actuator2),
    new Actuator(D3, 3, &settings.getSettings()->actuator3),
    new Actuator(D4, 4, &settings.getSettings()->actuator4),
    new Actuator(D5, 5, &settings.getSettings()->actuator5),
    new Actuator(D6, 6, &settings.getSettings()->actuator6),
    new Actuator(D7, 7, &settings.getSettings()->actuator7),
    new Actuator(D8, 8, &settings.getSettings()->actuator8)
};

void setup()
{ 
    Serial.begin(74880);
    while (! Serial) {
        delay(1);
    }

    settings.begin();
    wifi.begin();
    webServer.begin();

    for (int i=0; i<8; i++) {
        actuators[i]->begin();
    }

    wifi.connect();
    dataCollector.begin();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    dataCollector.loop();

    for (int i=0; i<8; i++) {
        actuators[i]->loop();
    }

    if (wifi.isInAPMode() && millis() > 300000L) {
        ESP.reset();
    }

    delay(100);
}
