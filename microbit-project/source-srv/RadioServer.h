#pragma once
#include "MicroBit.h"
#include "SerialServer.h"
#include "RadioPacket.h"

class SerialServer;

class RadioServer{
    public:
        RadioServer(MicroBit *ubit, uint16_t id);
        ~RadioServer();
        void init(SerialServer *serv);
        void receivePacket();
        void run();
        void initReceptor(RadioPacket *p);
        
    private:
        uint16_t ID;
        MicroBit *uBit;
        SerialServer *serialServer;
};