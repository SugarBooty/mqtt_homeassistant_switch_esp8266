#include <Arduino.h>
#include <PersistentStorage.hpp>
#include <ConfigPage.hpp>
#include <HardwareSerial.h>
#include <WifiHandler.hpp>
#include <GlobalConfig.hpp>
#include <PubSubClient.h>
#include <MqttHandler.hpp>

#include <HassDeviceManager.hpp>

/*##################################################################################
    //TODO add support for multiple device topics using JSON
    this branch is for that
    {
        temp: {
            ~: homeassistant/sensor/sensorBedroomT
            uniq_id: temp_sensor_bedroom,
            name: Temperature,
            unit: F
        }
        humidity: {
            ~: homeassistant/sensor/sensorBedroomH
            uniq_id: humidity_sensor_bedroom,
            name: Humidity,
            unit: %
        }
    }
*/


const char *AP_SSID_path     = "/conf/AP_SSID";
const char *CON_SSID_path    = "/conf/CON_SSID";
const char *CON_PWD_path     = "/conf/CON_PWD";
const char *MQTT_IP_path     = "/conf/MQTT_IP";
const char *MQTT_PORT_path   = "/conf/MQTT_PORT";
const char *DISC_path        = "/conf/DISC";

const uint8_t SETUP_BUTTON   = D1; // setup button pin D1
const uint8_t HEATER_PIN     = D2; // heater pin D2

PersistentStorage storage;
WifiHandler wifi;
WiFiClient espClient;
PubSubClient client(espClient);
MqttHandler mqtt_handler;

void setup() {
    delay(1000);
    //init and set heater pin low
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(HEATER_PIN, LOW);

    Serial.begin(115200);
    pinMode(SETUP_BUTTON, INPUT_PULLUP);
    if ( (digitalRead(SETUP_BUTTON) == LOW) || (storage.exists(DISC_path) == false) ) {
        // enter config page mode, hosts wifi network with webpage to configure it
        // TODO make the initializer of ConfigPage show the page
        ConfigPage server = ConfigPage();
        server.show_page();
    } else {
        // connect to saved wifi creds
        String saved_SSID = storage.read(CON_SSID_path);
        String saved_PWD  = storage.read(CON_PWD_path);
        wifi.begin(saved_SSID, saved_PWD);
        // connect to saved mqtt creds
        String saved_MQTT_IP   = storage.read(MQTT_IP_path);
        String saved_MQTT_Port = storage.read(MQTT_PORT_path);
        mqtt_handler.begin(saved_MQTT_IP, saved_MQTT_Port);
    }
}

void loop() {
    wifi.status_loop();
    mqtt_handler.loop();
}
