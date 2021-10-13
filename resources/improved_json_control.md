{
    temperature: {

    }
}

types of devices:
    - switch
    - binary sensor
    - sensor

{
    humidity: {
        type: sensor,
        data: humidity,
        config_topic: "homeassistant/sensor/bedroom_climate_sensorH/config"
        discovery: {
            "~":"homeassistant/sensor/bedroom_climate_sensor",
            "cmd_t":"~/set",
            "stat_t":"~/get",
            "uniq_id":"dan_bedroom_humidity",
            "name":"Bedroom Humidity",
            "optimistic":"false",
            "retain":"true"
        }
    },
    temperature: {
        type: sensor, 
        data: temperature,
        config_topic: "homeassistant/sensor/bedroom_climate_sensorT/config"
        discovery: {
            "~":"homeassistant/switch/bedroom_climate_sensor",
            "cmd_t":"~/set",
            "stat_t":"~/get",
            "uniq_id":"dan_bedroom_temperature",
            "name":"Bedroom Temperature",
            "optimistic":"false",
            "retain":"true"
        }
    }
}

for using pins as switches:
{
    heater: {
        type: switch,
        pin: 4,
        discovery: {
            "~": "homeassistant/switch/dan_bedroom_heater",
            "cmd_t": "~/set",
            "stat_t": "~/get",
            "uniq_id": "dan_bedroom_heater",
            "name": "Heater",
            "optimistic": "false",
            "retain": "true"
        }
    },
    light: {
        type: switch,
        pin: 5,
        discovery: {
            "~":"homeassistant/switch/dan_bedroom_lamp",
            "cmd_t":"~/set",
            "stat_t":"~/get",
            "uniq_id":"dan_bedroom_lamp",
            "name":"Dan Bedside Lamp",
            "optimistic":"false",
            "retain":"true"
        }
    }
}