#pragma once

#include "WiFi.h"


enum ActuatorType {
    NO = 0,
    NC = 1
};

struct ActuatorSettings {
    ActuatorType type;
};

const char ACTUATOR_CONFIG_PAGE[] PROGMEM = R"=====(
Actuator %d:
<select name="actuator_%d_type">
<option value="0" %s>NO</option>
<option value="1" %s>NC</option>
</select><br>
)=====";

enum ActuatorMode {
    OPEN = 1,
    CLOSE = 0
};

class Actuator {
    public:
        Actuator(uint8_t pin, uint8_t index, ActuatorSettings* settings);
        void begin();
        void loop();

        void open();
        void close();
        // Turn off the actuator. Designed to save power without the need to
        // consider is NO or NC actuator.
        void off();

        ActuatorMode get();

        void get_config_page(char* buffer);
        void parse_config_params(WebServerBase* webServer);
    private:
        uint8_t _pin;
        uint8_t _index;
        ActuatorMode _mode;
        ActuatorSettings* _settings;
};
