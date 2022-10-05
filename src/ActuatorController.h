#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "esp8266-base.h"

#include "Actuator.h"

#define HTTP_PORT 80
#define HOSTNAME "ufha-controller"

extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;
extern Actuator* actuators[];