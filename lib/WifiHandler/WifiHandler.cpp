#include <WifiHandler.hpp>
#include <ESP8266WiFi.h>

void WifiHandler::begin(String SSID, String PWD){
    WiFi.begin(SSID, PWD);
    Serial.print("Connecting");
    int connection_length = 0;
    while( WiFi.status() != WL_CONNECTED ) {
        delay(250);
        Serial.print(".");
        connection_length += 1;
        if ( connection_length > 40 ) {
            ESP.restart();
        }
    }
    Serial.println();
    Serial.print("Connected! IP addr: ");
    Serial.println(WiFi.localIP());
}

void WifiHandler::status_loop() {
    if ( WiFi.status() != WL_CONNECTED ) {
        ESP.restart();
    }
}