#include "MicroBit.h"
#include "Common.h"
#include "SensorData.h"

class SensorDataContainer{
    public:
        SensorDataContainer(MeasureType type);
        ~SensorDataContainer();
        int8_t* getBuffer();

    private:
        void addData(MeasureType type);
        uint16_t size;
        MeasureType type;
        SensorData *first
};