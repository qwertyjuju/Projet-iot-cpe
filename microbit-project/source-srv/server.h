#pragma once
#include "MicroBit.h"
#include "SerialServer.h"

class Server{
    public:
        Server(MicroBit *ubit);
        ~Server();
        void receivePacket();
        void run();
        
    private:
        MicroBit *uBit;
        SerialServer serialServer;
};