#include <GlobalConfig.hpp>
#include <JsonBuilder.hpp>
#include <PersistentStorage.hpp>
#include <ConfigPage.hpp>
#include <Webpage.hpp>


/*######################################################################################
  #  This class handles setting the ESP up in AP mode and launching the captive portal
  #  handler. When a user connects, it will ask them to log in. This is for easy access
  #  to the configuration page.
  #  
  #  The webpage has fields for:
  #      - what the ESP AP SSID should be
  #      - the wifi SSID and password it should connect to
  #      - the MQTT IP and port to connect to
  #      - the discovery JSON for Home Assistant
  #  
  #  The webpage will ensure the discovery JSON is formatted correctly, but does not
  #  ensure all the needed fields are in place for it to be a valid Home Assistant
  #  discovery configuration.
######################################################################################*/

extern const char *AP_SSID_path;
extern const char *CON_SSID_path;
extern const char *CON_PWD_path;
extern const char *MQTT_IP_path;
extern const char *MQTT_PORT_path;
extern const char *DISC_path;

DNSServer dnsServer;
AsyncWebServer server(80);

extern PersistentStorage storage;


// this is some kind of handler that sends a webpage to any request on the network
class CaptiveRequestHandler : public AsyncWebHandler {
public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request){
        return true;
    }

    // this is what it sent to every request
    // FIXME make this redirect to somewhere we can use SSL
    void handleRequest(AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(301);
        response->addHeader("Location", "http://192.168.4.1");
        response->addHeader("Cache-Control", "no-cache");
        request->send(response);
    }
};


// this makes the ESP enter AP mode and launches the async web server with a captive portal
void ConfigPage::show_page() {
    Serial.println("");
    Serial.println("Web page launched");
    String SSID = storage.read(AP_SSID_path);
    if ( SSID == "" ){
      SSID = "ESP_CONFIG";
    }
    WiFi.softAP(SSID);
    dnsServer.start(53, "*", WiFi.softAPIP());
    Serial.print("IP address: "); Serial.println(WiFi.softAPIP());
    setup_router();
    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP (no idea what this means honestly)
    server.begin();
    
    loop();
}

// sets the listeners for the web server
void ConfigPage::setup_router() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", CONFIG_PAGE);
        Serial.println("Client Connected");
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){

        JsonBuilder output_json;

        if ( storage.exists( AP_SSID_path) ){
          output_json.add_string("AP_SSID", storage.read(AP_SSID_path));
        }
        if ( storage.exists( CON_SSID_path) ){
          output_json.add_string("CON_SSID", storage.read(CON_SSID_path));
        }
        // if ( storage.exists( CON_PWD_path) ){
        //   output_json.add_string("CON_PWD", storage.read(CON_PWD_path));
        // }
        if ( storage.exists( MQTT_IP_path) ){
          output_json.add_string("MQTT_IP", storage.read(MQTT_IP_path));
        }
        if ( storage.exists( MQTT_PORT_path) ){
          output_json.add_string("MQTT_PORT", storage.read(MQTT_PORT_path));
        }
        if ( storage.exists( DISC_path) ){
          output_json.add_object("DISC", storage.read(DISC_path));
        }

        request->send(200, "text/html", output_json.formatted());
        Serial.println("Client Connected");
    });
    server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request){
        Serial.println("Submit button pressed");

        storage.write(AP_SSID_path, request->arg("AP_SSID"));
        storage.write(CON_SSID_path, request->arg("CON_SSID"));
        storage.write(CON_PWD_path, request->arg("CON_PWD"));
        storage.write(MQTT_IP_path, request->arg("MQTT_IP"));
        storage.write(MQTT_PORT_path, request->arg("MQTT_PORT"));
        storage.write(DISC_path, request->arg("DISC"));

        request->send(200, "text/html", "Config successfully updated");
    });
}

// processes the DNS requests every loop
// stays in here, doesnt continue
// TODO add continue button to website to continue bootup
void ConfigPage::loop() {
  // stay in this class until reboot
    while (true) {
      dnsServer.processNextRequest();
      yield();
    }
}
