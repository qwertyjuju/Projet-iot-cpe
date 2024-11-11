#pragma once
#include "MicroBit.h"

class SerialPacket{
    public:
        SerialPacket();
        ~SerialPacket();
        void setData(uint8_t* buffer, int datasize);
        void setOpCode(uint8_t code);
        uint8_t *getBuffer(); 
        uint16_t getSize();

    private:
        uint8_t opcode;
        uint8_t *data;
        uint16_t size;
};