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
        void reset();
        void init();
        MeasureType getTypes();
        void setDisplayOrder(uint8_t* order, int size);
        void set(int index , uint8_t value);
        void set(int index , uint16_t value);
        void set(int index , uint32_t value);
        void set(int index , int value);
        uint8_t getOrder(MeasureType index);
        
        
    private:
        uint8_t *buffer; // buffer pour stocker les données
        uint16_t buffersize;
        MeasureType measuredtypes; // type de mesures stockées
        uint8_t order[6]={0}; // ordre d'affichage des mesures
};