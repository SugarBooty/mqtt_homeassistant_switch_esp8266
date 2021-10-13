#pragma once
#include <HardwareSerial.h>
#include <PersistentStorage.hpp>

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"


class ConfigPage {
    private:

    public:
        // sets up ESP AP and configures Async Web Server in captive portal
        void show_page();

        // configures callbacks
        void setup_router();

        // processes DNS requests
        void loop();
};