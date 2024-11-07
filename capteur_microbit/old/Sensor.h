#pragma once
#include "Common.h"
#include "SensorData.h"
#include "incl/bme280.h"
#include "incl/ssd1306.h"
#include "incl/tsl256x.h"
#include "incl/veml6070.h"

typedef struct SensorDevice{
    SensorType type;
    union 
    {
        bme280* bme;
        tsl256x* tsl;
        veml6070* veml;
    }device;
};

class Sensor{
    public:
        Sensor(SensorDevice device);
        ~Sensor();
        SensorData read();
        void activate();
        void deactivate();
        bool isActive();
    
    private:
        bool active;
        SensorDevice device;
};