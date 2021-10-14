#include <MqttHandler.hpp>
#include <GlobalConfig.hpp>
#include <PubSubClient.h>
#include <IPAddress.h>
#include <ArduinoJson.h>
#include <PersistentStorage.hpp>

/*######################################################################################
    This class handles connecting to MQTT, subscribing to the correct topics, sending
    the discovery JSON configuration for Home Assistant, and recieving commands via the
    command topic then updating the status via the status topic
######################################################################################*/

extern PersistentStorage storage;
extern PubSubClient client;
extern uint8_t HEATER_PIN;

/*
this is the callback function that is called on data recieved from MQTT. It sees if the topic is 
the command topic for the heater, if it is, it does what the payload instructs it to do. Any message 
other than "ON" turns the heater "OFF"

//TODO make this use the payload and status messages defined in the discovery json if applicable, otherwise use default values
*/
void MqttHandler::callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0';
    Serial.print("Message Recieved! Payload: ");
    Serial.print(String((char*)payload));
    Serial.println("!");
    Serial.print("Topic: ");
    Serial.println(topic);
    if (String(topic) == command_topic)
    {
        Serial.println("Topic passed check");
        if (String((char*)payload) == "ON")
        // TODO Figure out a way to use HEATER_PIN instead of D2
        {
            Serial.println("Switching ON");
            digitalWrite(D2, HIGH);
            client.publish(status_topic.c_str(), "ON");
        }
        else
        {
            Serial.println("Switching OFF");
            digitalWrite(D2, LOW);
            client.publish(status_topic.c_str(), "OFF");
        }
    }

}

/*
Initializes the MQTT client with the server information, sets the callback to the member function "callback"
deserializes the discovery json and constructs the full command topic, status topic, and discovery topic.
Finally, runs connect member function
*/
void MqttHandler::begin(String MQTT_IP_S, String MQTT_PORT_S)
{
    uint16_t MQTT_PORT = MQTT_PORT_S.toInt();
    IPAddress MQTT_IP;
    MQTT_IP.fromString(MQTT_IP_S);
    client.setServer(MQTT_IP, MQTT_PORT);

    // using std::bind to make a member function a regular one for the callback
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    client.setCallback(std::bind( &MqttHandler::callback, this, _1,_2,_3));

    DeserializationError error = deserializeJson(doc, storage.read(DISC_path));

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    // constructs the various topics to use from the root and topic identifiers
    // in the discovery JSON configuration
    String topic_root = doc["~"];
    String topic_stat = doc["stat_t"];
    String topic_cont = doc["cmd_t"];

    status_topic = topic_root;
    topic_stat.remove(0, 1);
    status_topic += topic_stat;
    Serial.print("Status Topic:    ");
    Serial.println(status_topic);

    command_topic = topic_root;
    topic_cont.remove(0, 1);
    command_topic += topic_cont;
    Serial.print("Command Topic:   ");
    Serial.println(command_topic);

    discovery_topic = topic_root;
    discovery_topic += "/config";
    Serial.print("Discovery Topic: ");
    Serial.println(discovery_topic);

    connect();
}
/*
Used to initially connect or reconnect upon loss of connection.
If not connected to mqtt, connect using the unique ID specified in the discovery json.
If successfully connected, subscribe to the command topic and send the discovery json
to the discovery topic for HASS
*/

void MqttHandler::connect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect( doc["uniq_id"] ))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.subscribe( command_topic.c_str());
            for (int x; x > 250; x++) {
                client.loop();
            }
            String discovery_json = storage.read(DISC_path);
            discovery_json.replace("\n", "");
            // client.publish( const_cast<char *>(discovery_topic.c_str()), const_cast<char *>(discovery_json.c_str()) );   // limited to 256 bytes including header
            client.beginPublish(discovery_topic.c_str(), discovery_json.length(), false);
            client.print(discovery_json.c_str());
            client.endPublish();
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 1 second before retrying
            delay(1000);
        }
    }
}

void MqttHandler::publish(const char* topic, const char* payload, const bool retain){
    client.publish(topic, payload, retain);
}
/*
this is the loop run in the loop to ensure MQTT is connected and to process commands sent to the command topic
*/
void MqttHandler::loop()
{
    if (!client.connected())
        connect();
    client.loop();
}