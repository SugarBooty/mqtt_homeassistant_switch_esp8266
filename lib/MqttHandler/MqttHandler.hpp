#include <Arduino.h>
#include <IPAddress.h>
#include <ArduinoJson.h>

class MqttHandler {
    private:
        String status_topic;
        String command_topic;
        String discovery_topic;
        // the discovery JSON is stored to be able to pull from it
        // TODO only store the unique ID and other things that are needed to save space
        // This was done because storing the char* ended up going out of scope and garbage was pulled from memory
        StaticJsonDocument<256> doc;

    public:
        // callback function to process incoming subscriptions
        void callback(char* topic, byte* payload, unsigned int length);
        // begins the MQTT client
        void begin(String MQTT_IP, String MQTT_PORT);
        // connects to the MQTT broker
        void connect();
        // loop for updating
        void loop();
};