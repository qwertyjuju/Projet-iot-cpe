#pragma once
#include "MicroBit.h"
#include "RadioPacket.h"
#include "SensorReader.h"
#include "SensorData.h"
#include "Display.h"

// Classe SensorServer pour gérer les communications avec le serveur
class SensorServer{
    public :
        SensorServer(MicroBit* ubit, MicroBitI2C *i2c, MicroBitPin *P0);
        ~SensorServer();
        void run();
        void init();
        void InitConnection();
        void receivepacket();
        void sendData(SensorData *sData);

    private :
        ManagedString SN;
        MicroBit *uBit;
        uint16_t ID;
        uint16_t IDDst;
        MicroBitI2C *i2c;
        MicroBitPin *P0;
        SensorReader *sReader;
        Display *display;
        uint8_t state;
        
};