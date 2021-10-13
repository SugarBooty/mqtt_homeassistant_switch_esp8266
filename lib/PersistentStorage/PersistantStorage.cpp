// #include <GlobalConfig.hpp>
#include <PersistentStorage.hpp>
#include <FS.h>

PersistentStorage::PersistentStorage(){
    if (!SPIFFS.begin()) {
        Serial.println("Could not start SPIFFS");
    } else {
        Serial.println("Started SPIFFS");
    }
}

bool PersistentStorage::write(const char *file_name, String file_content){
    bool success = false;
    SPIFFS.remove(file_name);
    File file = SPIFFS.open(file_name, "w");
    if (file.print(file_content)) {
        success = true;
        Serial.print(file_name);
        Serial.println(" written");
    } else {
        Serial.print(file_name);
        Serial.println(" FAILED TO WRITE!!!!!!!!!!!!!!!!");
    }
    file.close();
    return success;
}

String PersistentStorage::read(const char *file_name){
    File file = SPIFFS.open(file_name, "r");
    String content = file.readString();
    file.close();
    Serial.print(file_name);
    Serial.println(" read");
    return content;
}

bool PersistentStorage::exists( const char* file_name){
    return SPIFFS.exists(String(file_name));
}