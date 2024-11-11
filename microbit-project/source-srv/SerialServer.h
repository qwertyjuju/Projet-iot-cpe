#pragma once
#include "MicroBit.h"
#include "RadioServer.h"
#include "SerialPacket.h"

class RadioServer;
class SerialServer{
    public:
        SerialServer(MicroBit *ubit);
        ~SerialServer();
        void sendMessage(ManagedString str);
        void init(RadioServer *serv);
        void receiveData();
        void sendPacket(SerialPacket *p);

    private:
        MicroBit *uBit;
        RadioServer *radioServer;
};