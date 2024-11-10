#pragma once
#include "MicroBit.h"
#include "incl/ssd1306.h"
#include "SensorData.h"
#include "Common.h"

class Display{
    public:
        Display(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *pin);
        ~Display();
        void setupScreen(SensorData *data);
        void render();

    private:
        ssd1306 screen;
        MicroBit *uBit;
};