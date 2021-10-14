#include <HassSwitch.hpp>

//moved to HassDeviceManager.cpp

// HassSwitch::HassSwitch(const int pin, const String command_topic, const String status_topic, const bool retain) {
//     m_pin = pin;
//     m_command_topic = command_topic;
//     m_status_topic = status_topic;
//     m_retain = retain;
//     pinMode(m_pin, OUTPUT);
//     digitalWrite(m_pin, LOW);
//     mqtt_handler.publish(m_status_topic.c_str(), "OFF", m_retain);
// }

// void HassSwitch::process_payload(const char* payload) {
//     if (payload == "ON") {
//         digitalWrite(m_pin, HIGH);
//         mqtt_handler.publish(m_status_topic.c_str(), "ON", m_retain);
//     } else {
//         digitalWrite(m_pin, LOW);
//         mqtt_handler.publish(m_status_topic.c_str(), "OFF", m_retain);
//     }
// }
