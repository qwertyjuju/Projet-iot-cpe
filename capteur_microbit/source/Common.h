#pragma once
#include "MicroBit.h"

// defini les types de mesures (binaire)
typedef enum {
        TEMPERATURE = 1<<0,
        PRESSURE= 1<<1,
        HUMIDITY= 1<<2,
        LUX=1<<3,
        IR=1<<4,
        UV= 1<<5
}MeasureType;

//surcharge de l'opérateur | pour combiner plusieurs types de mesure
inline MeasureType operator|(MeasureType a, MeasureType b)
{
    return static_cast<MeasureType>(static_cast<int>(a) | static_cast<int>(b));
}

//fonction pour comparer deux buffers de taille `size`
// Retourne true si les buffers sont identiques, sinon false
inline bool compare(uint8_t *buffer1, uint8_t *buffer2, int size){
    for(int i=0; i<size; i++){
        if(buffer1[i]!= buffer2[i])
            return false;
    }
    return true;
}

