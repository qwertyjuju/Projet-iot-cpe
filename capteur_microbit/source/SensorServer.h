#pragma once
#include "MicroBit.h"
#include "SensorReader.h"
#include "SensorData.h"
#include "Display.h"
class SensorServer{
    public :
        SensorServer(MicroBit* ubit, MicroBitI2C *i2c, MicroBitPin *P0);
        ~SensorServer();
        void run();
        //void init();
        //void receivepacket();


    private :
        MicroBit *uBit;
        uint16_t ID;
        SensorReader sReader;
        Display display;
};