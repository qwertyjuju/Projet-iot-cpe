#include "MicroBit.h"
#include "Common.h"


class SensorData{
    public: 
        SensorData(MeasureType type);

    private:
        MeasureType type;
        union{
            uint8_t value8;
            uint8_t value16;
            uint8_t value32;
        };
};