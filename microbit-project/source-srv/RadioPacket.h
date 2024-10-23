#pragma once
#include "MicroBit.h"

class RadioPacket{
    public: 
        RadioPacket(PacketBuffer p);
        ~RadioPacket();
    
    private:
        PacketBuffer buffer;
        char opcode;
        char idSource[2];
        char idDest[2];
        char *data;
        char checksum;

};