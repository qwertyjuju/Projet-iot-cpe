#pragma once

typedef enum {
        TEMPERATURE = 1<<0,
        PRESSURE= 1<<1,
        HUMIDITY= 1<<2,
        LUX=1<<3,
        IR=1<<4,
        UV= 1<<5
}MeasureType;


inline MeasureType operator|(MeasureType a, MeasureType b)
{
    return static_cast<MeasureType>(static_cast<int>(a) | static_cast<int>(b));
}
