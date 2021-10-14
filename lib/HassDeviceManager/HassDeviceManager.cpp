#include <HassDeviceManager.hpp>

void HassDeviceManager::initialize(StaticJsonDocument<1024> json) {
    // TODO make this deconstruct the json document and make objects based on it
    const char* mode = "switch"; // temporary

    if ( mode == "switch" ) {
        HassSwitch switch1(3, "homeassistant/switch/aaaa", "homeassistant/assd", false); // example
        m_all_devices.push_back(switch1);
    }
    
}

void HassDeviceManager::route_payload(const char* topic, const char* payload) {
    for ( Device device : m_all_devices) {
        if (device.m_command_topic == topic){
            device.process_payload(payload);
        }
    }
}

// moved from HassSwitch.cpp

HassSwitch::HassSwitch(const int pin, const String command_topic, const String status_topic, const bool retain) {
    m_pin = pin;
    m_command_topic = command_topic;
    m_status_topic = status_topic;
    m_retain = retain;
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
    mqtt_handler.publish(m_status_topic.c_str(), "OFF", m_retain);
}

void HassSwitch::process_payload(const char* payload) {
    if (payload == "ON") {
        digitalWrite(m_pin, HIGH);
        mqtt_handler.publish(m_status_topic.c_str(), "ON", m_retain);
    } else {
        digitalWrite(m_pin, LOW);
        mqtt_handler.publish(m_status_topic.c_str(), "OFF", m_retain);
    }
}