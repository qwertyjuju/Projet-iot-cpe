#pragma once
#include "MicroBit.h"
#include "Common.h"

class SensorData{
    public:
        SensorData(MeasureType type);
        ~SensorData();
        uint16_t getSize();
        uint8_t *getBuffer();
        void setTypes(MeasureType type);
        void setTypes(uint8_t *buffer, int length);
        void reset();
        void init();
        MeasureType getTypes();
        void set(int index , uint8_t value);
        void set(int index , uint16_t value);
        void set(int index , uint32_t value);
        void set(int index , int value);
        
        
    private:
        uint8_t *buffer;
        uint16_t buffersize;
        MeasureType measuredtypes;

};