#include "ActuatorController.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger, systemCheck) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/open", std::bind(&WebServer::handle_open, this));
    server->on("/close", std::bind(&WebServer::handle_close, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);
    dataCollector.parse_config_params(this);
    actuators[0]->parse_config_params(this);
    actuators[1]->parse_config_params(this);
    actuators[2]->parse_config_params(this);
    actuators[3]->parse_config_params(this);
    actuators[4]->parse_config_params(this);
    actuators[5]->parse_config_params(this);
    actuators[6]->parse_config_params(this);
    actuators[7]->parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char data_collector_settings[strlen_P(INFLUXDB_CONFIG_PAGE) + 64];
    dataCollector.get_config_page(data_collector_settings);

    char actuator0_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[0]->get_config_page(actuator0_config_page);

    char actuator1_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[1]->get_config_page(actuator1_config_page);

    char actuator2_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[2]->get_config_page(actuator2_config_page);

    char actuator3_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[3]->get_config_page(actuator3_config_page);

    char actuator4_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[4]->get_config_page(actuator4_config_page);

    char actuator5_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[5]->get_config_page(actuator5_config_page);

    char actuator6_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[6]->get_config_page(actuator6_config_page);

    char actuator7_config_page[strlen_P(ACTUATOR_CONFIG_PAGE) + 32];
    actuators[7]->get_config_page(actuator7_config_page);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        data_collector_settings,
        actuator0_config_page,
        actuator1_config_page,
        actuator2_config_page,
        actuator3_config_page,
        actuator4_config_page,
        actuator5_config_page,
        actuator6_config_page,
        actuator7_config_page);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_open() {
     if (server->args() != 1
        || server->arg(0).length() != 0
        || server->argName(0).length() != 1) {
        server->send(400, "text/plain", "try with /heat?3");
        return;
    }

    uint8_t actuator_index = atoi(server->argName(0).c_str());
    if (actuator_index < 1 || actuator_index > 8) {
        server->send(400, "text/plain", "supported actuator indexes are 1 to 8");
        return;
    }

    actuators[actuator_index-1]->open();

    server->send(200);
}

void WebServer::handle_close() {
     if (server->args() != 1
        || server->arg(0).length() != 0
        || server->argName(0).length() != 1) {
        server->send(400, "text/plain", "try with /cool?3");
        return;
    }

    uint8_t actuator_index = atoi(server->argName(0).c_str());
    if (actuator_index < 1 || actuator_index > 8) {
        server->send(400, "text/plain", "supported actuator indexes are 1 to 8");
        return;
    }

    actuators[actuator_index-1]->close();

    server->send(200);
}

void WebServer::handle_get() {
    sprintf_P(buffer,
              GET_JSON,
              actuators[0]->get(),
              actuators[1]->get(),
              actuators[2]->get(),
              actuators[3]->get(),
              actuators[4]->get(),
              actuators[5]->get(),
              actuators[6]->get(),
              actuators[7]->get());
    server->send(200, "application/json", buffer);
}

void WebServer::handle_off() {
    for (int i = 0; i < 8; i++) {
        actuators[i]->off();
    }
    server->send(200);
}