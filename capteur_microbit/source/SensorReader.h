#pragma once

#include "Common.h"
#include "SensorData.h"
#include "MicroBit.h"
#include "incl/bme280.h"
#include "incl/tsl256x.h"
#include "incl/veml6070.h"

class SensorReader{
    public:  
        SensorReader(MicroBit *ubit, MicroBitI2C *i2c,MeasureType type);
        ~SensorReader();
/*         void addMeasuredType(MeasureType atype);
        void removeMeasuredType(MeasureType rtype); */
        SensorData *read();
    
    private:
        MicroBit *uBit;
        bme280 tphSensor; // Température, Pression, Humidité
        tsl256x liSensor; // Lux, IR
        veml6070 uvSensor; // UV
        SensorData data;
};