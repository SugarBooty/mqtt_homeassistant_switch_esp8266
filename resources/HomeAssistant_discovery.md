What is needed for the discover topic of HomeAssistant for it to register correctly:

switch:
  - platform: mqtt
x    unique_id: bedroom_switch
x    name: "Bedroom Switch"
x    state_topic: "home/bedroom/switch1"
x    command_topic: "home/bedroom/switch1/set"
x    availability:
x      - topic: "home/bedroom/switch1/available"
x    payload_on: "ON"
x    payload_off: "OFF"
x    state_on: "ON"
x    state_off: "OFF"
x    optimistic: false
    qos: 0
    retain: true