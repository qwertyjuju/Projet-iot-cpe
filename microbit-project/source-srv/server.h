#pragma once
#include "MicroBit.h"
#include "SerialServer.h"

class Server{
    public:
        Server(MicroBit *ubit, uint16_t id);
        ~Server();
        void receivePacket();
        void run();
        
    private:
        uint16_t ID;
        MicroBit *uBit;
        SerialServer serialServer;
};