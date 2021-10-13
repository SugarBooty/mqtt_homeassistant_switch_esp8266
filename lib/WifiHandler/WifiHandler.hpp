#pragma once
#include <Arduino.h>

class WifiHandler {
    private:

    public:
        void begin(String SSID, String PWD);
        void status_loop();
        void callback(char*, uint8_t*, unsigned int);
};