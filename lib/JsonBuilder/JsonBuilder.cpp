#include "JsonBuilder.hpp"

JsonBuilder::JsonBuilder() {
    json_buffer = "{";
}

void JsonBuilder::add_string( String key, String val) {
    json_buffer += "\"";
    json_buffer += key;
    json_buffer += "\":\"";
    json_buffer += val;
    json_buffer += "\",";
}

void JsonBuilder::add_object( String key, String obj) {
    json_buffer += "\"";
    json_buffer += key;
    json_buffer += "\":";
    json_buffer += obj;
}

String JsonBuilder::formatted() {
    // int len = json_buffer.length();
    // json_buffer.remove(len-1, 1);
    json_buffer += "}";
    return json_buffer;
}

// {
//     "NAME": "name of thing",
//     "DISC": {
//         "BLAH": "VAL",
//         "OOP": "VAL",
//     }
// }