#include "ActuatorController.h"

Actuator::Actuator(uint8_t pin, uint8_t index, ActuatorSettings* settings) {
    this->_pin = pin;
    this->_index = index;
    this->_settings = settings;
    pinMode(_pin, OUTPUT);
}

void Actuator::begin() {
    this->off();
}

void Actuator::loop() {
    uint8_t value;
    if (this->_mode == OPEN) {
        value = (this->_settings->type == NO)?LOW:HIGH;
    } else {
        value = (this->_settings->type == NO)?HIGH:LOW;
    }
    digitalWrite(this->_pin, value);
}

void Actuator::open() {
    this->_mode = OPEN;
}

void Actuator::close() {
    this->_mode = CLOSE;
}

ActuatorMode Actuator::get() {
    return this->_mode;
}

void Actuator::off() {
    digitalWrite(this->_pin, LOW);
    this->_mode = (this->_settings->type == NO)?OPEN:CLOSE;
}

void Actuator::get_config_page(char* buffer) {
    sprintf_P(
        buffer,
        ACTUATOR_CONFIG_PAGE,
        _index,
        _index,
        (this->_settings->type == NO)?"selected":"",
        (this->_settings->type == NC)?"selected":"");
}

void Actuator::parse_config_params(WebServerBase* webServer) {
    String idx(_index);

    uint8_t type_value = 2;
    webServer->process_setting(("actuator_" + idx + "_type").c_str(), type_value);
    if (type_value == 0) {
        this->_settings->type = NO;
    } else if (type_value == 1) {
        this->_settings->type = NC;
    }
}