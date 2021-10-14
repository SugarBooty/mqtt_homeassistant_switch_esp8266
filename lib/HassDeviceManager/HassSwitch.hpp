#include <Arduino.h>
#include <MqttHandler.hpp>


extern MqttHandler mqtt_handler;

// moved to HassDeviceManager.hpp

// class HassSwitch: public virtual Device {

//     private:
//         int m_pin;
//         String m_command_topic;
//         String m_status_topic;
//         bool m_retain;
//         bool m_state;



//     public:
//         // initializes the device object
//         HassSwitch(const int pin, const String command_topic, const String status_topic, const bool retain);
//         // processes the payload given to it
//         void process_payload(const char* payload);



// };