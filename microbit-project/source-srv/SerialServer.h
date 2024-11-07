#pragma once
#include "MicroBit.h"
#include "RadioServer.h"

class RadioServer;
class SerialServer{
    public:
        SerialServer(MicroBit *ubit);
        ~SerialServer();
        void sendString(ManagedString str);
        void init(RadioServer *serv);
        void receiveData();

    private:
        MicroBit *uBit;
        RadioServer *radioServer;
};