#pragma once

#include "SettingsBase.h"
#include "WiFi.h"
#include "Actuator.h"

struct SettingsData {
    NetworkSettings network;
    ActuatorSettings actuator1;
    ActuatorSettings actuator2;
    ActuatorSettings actuator3;
    ActuatorSettings actuator4;
    ActuatorSettings actuator5;
    ActuatorSettings actuator6;
    ActuatorSettings actuator7;
    ActuatorSettings actuator8;
};

struct Empty {};

class Settings: public SettingsBase<SettingsData, Empty> {
    public:
        Settings();
        SettingsData* getSettings();

    protected:
        void initializeSettings();
        Empty* getRTCSettings();

    private:
        SettingsData settingsData;
};
