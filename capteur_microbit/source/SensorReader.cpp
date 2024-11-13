#include "SensorReader.h"

SensorReader::SensorReader(MicroBit *ubit, MicroBitI2C *i2c,MeasureType type): tphSensor(ubit, i2c), liSensor(ubit, i2c), uvSensor(ubit, i2c), data(type){
    uBit = ubit;
}
SensorReader::~SensorReader(){
    
}

// Methode pour lire et stocker les données des capteurs
SensorData *SensorReader::read(){
    data.reset();
    data.init();
    int t=0, p=0, h=0;
    uint32_t lux = 0;
    uint16_t ir = 0, uv = 0;
    MeasureType measuredtypes = data.getTypes();

    // Lecture des données des capteurs
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

    // Ajout des données dans le buffer
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

// Methode pour définir l'ordre d'affichage des données
void SensorReader::setDisplayOrder(uint8_t* order, int size){
    data.setDisplayOrder(order, size);
}