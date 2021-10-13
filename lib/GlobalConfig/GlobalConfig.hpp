#pragma once
// #include <ConfigPage.hpp>
// #include <Webpage.hpp>
// #include <JsonBuilder.hpp>
// #include <PersistentStorage.hpp>

#include <Arduino.h>
#include <pgmspace.h>
#include <FS.h>
#include <PubSubClient.h>

extern const char *AP_SSID_path;
extern const char *CON_SSID_path;
extern const char *CON_PWD_path;
extern const char *MQTT_IP_path;
extern const char *MQTT_PORT_path;
extern const char *DISC_path;

extern PubSubClient client;
// extern uint8_t HEATER_PIN;

// extern PersistentStorage storage;
// extern WifiHandler wifi;
// extern WiFiClient espClient;
// extern PubSubClient client(espClient);


// const char *UNIQUE_ID = "5984dd9c-0963-4d94-804f-269a66fc707e";

// const char []DEFAULT_JSON_CONFIG PROGMEM = R"

// "
