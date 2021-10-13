#pragma once
#include <Arduino.h>

class JsonBuilder{
    private:
        // the buffer that is added to when a key value pair is addd to json
        String json_buffer;

    public:
        JsonBuilder();
        // adds a key value pair to the json string being built
        void add_string( String key, String val);

        // adds nested object to json
        void add_object( String key, String obj);

        // returns the formatted json string
        String formatted();
};