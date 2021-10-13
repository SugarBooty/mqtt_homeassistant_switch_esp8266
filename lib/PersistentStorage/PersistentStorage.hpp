#pragma once
#include <Arduino.h>

class PersistentStorage{
    private:

    public:
        PersistentStorage();

        bool write( const char *file_name, String file_content );

        String read( const char *file_name );

        bool exists( const char* file_name );
};
