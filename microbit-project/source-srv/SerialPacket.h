#pragma once
#include "MicroBit.h"

class SerialPacket{
    public:
        SerialPacket();
        SerialPacket(MicroBit *uBit, uint8_t *buffer, int length);
        ~SerialPacket();
        void setData(uint8_t* buffer, int datasize);
        void setOpCode(uint8_t code);
        uint8_t *getData(); 
        uint16_t getDataSize();
        int getErrorCode();
        void setErrorCode(int code);
        ManagedString getError();
        uint8_t getOpCode();


    private:
        uint8_t opcode;
        uint8_t *data;
        uint8_t *buffer;
        uint16_t datasize;
        int errornb;
};