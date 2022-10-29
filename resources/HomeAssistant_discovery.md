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


discovery topic: home/sensor/sensorZDBedroomT/config
discovery topic: home/sensor/sensorZDBedroomH/config

sensor_t:
  name: "ZD Temp"
  stat_t: "home/zdbedroom/temp1"
  unit_of_meas: "°"
  val_tpl: "{{ value_json.t }}"

sensor_t:
  { "device_class": "temperature","name": "ZD Temp","stat_t": "home/zdbedroom/temp1","unit_of_meas": "°","val_tpl": "{{ value_json.t }}" }

sensor_h:
  name: "ZD Humidity"
  stat_t: "home/zdbedroom/temp1"
  unit_of_meas: "%"
  val_tpl: "{{ value_json.h }}"

  { "device_class": "humidity","name": "ZD Humidity","stat_t": "home/zdbedroom/temp1","unit_of_meas": "%","val_tpl": "{{ value_json.h }}" }
