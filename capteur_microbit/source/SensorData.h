#pragma once
#include "MicroBit.h"
#include "Common.h"

class SensorData{
    public:
        SensorData();
        ~SensorData();
        uint16_t getSize();
        uint8_t *getBuffer();
        void incrementBufferSize(MeasureType type);
        void decrementBufferSize(MeasureType type);
        void reset();
        void init();
        void set(int index , uint8_t value);
        void set(int index , uint16_t value);
        void set(int index , uint32_t value);
        void set(int index , int value);
        
        
    private:
        uint8_t *buffer;
        uint16_t buffersize;

};