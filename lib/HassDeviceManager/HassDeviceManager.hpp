#include <Arduino.h>
#include <HassSwitch.hpp>
#include <MqttHandler.hpp>
#include <ArduinoJson.h>
#include <Vector.h>


class HassDeviceManager{
    
    private:
        // MqttHandler mqtt_handler;
        Vector<Device> m_all_devices;

    public:
        // loads the whole json file and processes through it to create the device objects
        void initialize(StaticJsonDocument<1024> json);
        // takes in the payload recieved from MQTT and routes it to the device object it corresponds to based on the topic
        void route_payload(const char* topic, const char* payload);
        // does any housekeeping loop stuff the objects might require
        void loop();

};

class Device{
    public:
        String m_command_topic;
        virtual void process_payload(const char* payload);
};

// moved from HassSwitch.hpp
class HassSwitch: public virtual Device {

    private:
        int m_pin;
        // String m_command_topic;
        String m_status_topic;
        bool m_retain;
        bool m_state;



    public:
        // initializes the device object
        HassSwitch(const int pin, const String command_topic, const String status_topic, const bool retain);
        // processes the payload given to it
        void process_payload(const char* payload);



};