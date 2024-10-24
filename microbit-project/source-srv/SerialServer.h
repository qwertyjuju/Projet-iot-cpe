#pragma once
#include "MicroBit.h"

class SerialServer{
    public:
        SerialServer(MicroBit *ubit);
        ~SerialServer();
        void sendString(ManagedString str);

    private:
        MicroBit *uBit;
};