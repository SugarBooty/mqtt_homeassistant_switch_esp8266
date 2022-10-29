~: homeassistent/bedroom/heaterswitch
uniq_id: floor_heater
name: "Radiant Heater"
cmd_t: ~/set
payload_on: "ON"
payload_off: "OFF"
stat_t: ~/state
state_on: "ON"
state_off: "OFF"
qos: 0

ex: '{ "~": "homeassistent/bedroom/heaterswitch", "uniq_id": "dan_bedroom_heater", "name": "Bedroom Heater", "cmd_t": "~/set"}'


current:
- platform: mqtt
    command_topic: "home/bedroom/heater/set"
    state_topic: "home/bedroom/heater/get"
    state_off: "OFF"
    state_on: "ON"
    unique_id: bedroom_heater
    name: "Heater"
    optimistic: false
    retain: true
    qos: 1

{
    "~":"homeassistant/switch/radiant_heater",
    "cmd_t":"~/set",
    "stat_t":"~/get",
    "uniq_id":"floor_heater",
    "name":"Radiant Heater",
    "optimistic":"false",
    "retain":"true"
}


temp sensor:
- platform: mqtt
    name: "Temperature"
    state_topic: "home/node/1/temp_humidity/state"
    unit_of_measurement: "°F"
    value_template: "{{ value_json.temperature }}"
- platform: mqtt
    name: "Humidity"
    state_topic: "home/node/1/temp_humidity/state"
    unit_of_measurement: "%"
    value_template: "{{ value_json.humidity }}"
- platform: mqtt
    name: "Thermostat Set Point"
    state_topic: "home/nodered/set_temp"