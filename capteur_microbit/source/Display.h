#pragma once
#include "MicroBit.h"
#include "incl/ssd1306.h"
#include "SensorData.h"
#include "Common.h"

class Display{
    public:
        Display(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *pin);
        ~Display();
        void init();
        void setMessage(ManagedString string);   
        void setupScreen(SensorData *data);
        void render();
        void clear();

    private:
        ssd1306 screen;
};