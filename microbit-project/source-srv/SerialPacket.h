#pragma once
#include "MicroBit.h"

class SerialPacket{
    public:
        SerialPacket();
        ~SerialPacket();

    private:
        uint8_t *buffer;
};