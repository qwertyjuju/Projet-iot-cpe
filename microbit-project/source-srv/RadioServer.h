#pragma once
#include "MicroBit.h"
#include "SerialServer.h"
#include "RadioPacket.h"
#include "SerialPacket.h"

class SerialServer;

class RadioServer{
    public:
        RadioServer(MicroBit *ubit, uint16_t id);
        ~RadioServer();
        void init(SerialServer *serv);
        void receivePacket();
        void run();
        void initReceptor(RadioPacket *p);
        void processSerialPacket(SerialPacket p);
        
    private:
        uint16_t ID;
        MicroBit *uBit;
        SerialServer *serialServer;
};