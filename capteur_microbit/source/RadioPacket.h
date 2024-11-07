#pragma once
#include "MicroBit.h"
//#include <openssl/aes.h>

class RadioPacket{
    public: 
        RadioPacket(PacketBuffer *p, uint16_t idserv);
        ~RadioPacket();
        int getErrorCode();
        ManagedString getError();
        uint8_t getOpCode();
        uint16_t getSource();
        uint16_t getDest();
        PacketBuffer *getBuffer();
        uint16_t getDataSize();
        void encrypt();
        void decrypt();
    
    private:
        void setErrorCode(int code);
        PacketBuffer *buffer;
        uint16_t idServ;
        uint8_t opcode;
        uint16_t idSource;
        uint16_t idDest;
        uint16_t dataSize;
        uint8_t *data;
        uint16_t* checksum;
        int errornb;
};