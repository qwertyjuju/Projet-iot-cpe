#pragma once
#include "MicroBit.h"
#include "Common.h"

class SensorData{
    public:
        SensorData(MicroBit *ubit, MeasureType type);
        ~SensorData();
        uint16_t getSize();
        uint8_t *getBuffer();
/*         void incrementBufferSize(MeasureType type);
        void decrementBufferSize(MeasureType type); */
        void setTypes(MeasureType type);
        void reset();
        void init();
        MeasureType getTypes();
        void set(int index , uint8_t value);
        void set(int index , uint16_t value);
        void set(int index , uint32_t value);
        void set(int index , int value);
        
        
    private:
        MicroBit *uBit;
        uint8_t *buffer;
        uint16_t buffersize;
        MeasureType measuredtypes;

};