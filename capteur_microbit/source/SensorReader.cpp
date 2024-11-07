#include "SensorReader.h"

SensorReader::SensorReader(MicroBit *ubit, MicroBitI2C *i2c,MeasureType type): tphSensor(ubit, i2c), liSensor(ubit, i2c), uvSensor(ubit, i2c){
    measuredtypes = type;
    buffersize=0;
    for (int bit = 1; bit <= (int) MeasureType::UV; bit <<= 1)
    {
        switch((MeasureType) bit & type){
            case TEMPERATURE:
                addMeasuredType(TEMPERATURE);
                break;
            case HUMIDITY:
                addMeasuredType(HUMIDITY);
                break;
            case PRESSURE:
                addMeasuredType(PRESSURE);
                break;
            case LUX:
                addMeasuredType(LUX);
                break;
            case IR:
                addMeasuredType(IR);
                break;
            case UV:
                addMeasuredType(UV);
                break;
        }
    }
}
SensorReader::~SensorReader(){
    
}
void SensorReader::addMeasuredType(MeasureType atype){
    if(!(measuredtypes&atype))
    {
        measuredtypes = measuredtypes|atype;
        data.incrementBufferSize(atype);
    }
}

void SensorReader::removeMeasuredType(MeasureType rtype){
    measuredtypes = (MeasureType)(measuredtypes&(~rtype));
    if(!(measuredtypes&rtype))
    {
        measuredtypes = measuredtypes|rtype;
        data.decrementBufferSize(rtype);
    }
}

SensorData *SensorReader::read(){
    data.reset();
    data.init();
    int t=0, p=0, h=0;
    uint32_t lux = 0;
    uint16_t ir = 0, uv = 0;
    if(measuredtypes&(TEMPERATURE|PRESSURE|HUMIDITY)){
        uint32_t temp_p;
        int32_t temp_t;
        uint16_t temp_h;
        tphSensor.sensor_read(&temp_p, &temp_t, &temp_h);
        t = tphSensor.compensate_temperature(temp_t);
        p = tphSensor.compensate_pressure(temp_p) / 100;
        h = tphSensor.compensate_humidity(temp_h);
    }
    if(measuredtypes&(IR|LUX)){
        liSensor.sensor_read(NULL, &ir, &lux);
    }
    if(measuredtypes&UV){
        uvSensor.sensor_read(&uv);
    }
    int j=0;
    for (int bit = 1; bit <= (int) MeasureType::UV; bit <<= 1)
    {
        switch((MeasureType) bit & measuredtypes){
            case TEMPERATURE:
                data.set(j, (uint8_t)TEMPERATURE);
                data.set(j+1, t);
                j+=5;
                break;
            case HUMIDITY:
                data.set(j, (uint8_t)HUMIDITY);
                data.set(j+1, h);
                j+=5;
                break;
            case PRESSURE:
                data.set(j, (uint8_t)PRESSURE);
                data.set(j+1, p);
                j+=5;
                break;
            case LUX:
                data.set(j, (uint8_t)LUX);
                data.set(j+1, lux);
                j+=5;
                break;
            case IR:
                data.set(j, (uint8_t)IR);
                data.set(j+1, ir);
                j+=3;
                break;
            case UV:
                data.set(j, (uint8_t)UV);
                data.set(j+1, uv);
                j+=3;
                break;
        }
    }
    return &data;
}