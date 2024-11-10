#pragma once
#include "MicroBit.h"
#include "RadioPacket.h"
#include "SensorReader.h"
#include "SensorData.h"
#include "Display.h"
class SensorServer{
    public :
        SensorServer(MicroBit* ubit, MicroBitI2C *i2c, MicroBitPin *P0);
        ~SensorServer();
        void run();
        void init();
        void InitConnection();
        void receivepacket(MicroBitEvent);


    private :
        ManagedString SN;
        MicroBit *uBit;
        uint16_t ID;
        SensorReader sReader;
        Display display;
        uint8_t state;
};