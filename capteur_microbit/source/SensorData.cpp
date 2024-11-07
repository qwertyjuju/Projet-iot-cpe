#include "SensorData.h"

SensorData::SensorData(){
    this->buffersize= 0;
}
SensorData::~SensorData(){
    free(buffer);    
}

void SensorData::init(){
    buffer = (uint8_t*) malloc(buffersize);
}
void SensorData::reset(){
    free(buffer);
}
void SensorData::incrementBufferSize(MeasureType type){
        if(type&TEMPERATURE){
            buffersize+=5;
        }
        if(type&HUMIDITY){
            buffersize+=5;
        }
        if(type&PRESSURE){
            buffersize+=5;
        }
        if(type&LUX){
            buffersize+=5;
        }
        if(type&UV){
            buffersize+=3;
        }
        if(type&IR){
            buffersize+=3;
        }
}

void SensorData::decrementBufferSize(MeasureType type){
        if(type&TEMPERATURE){
            buffersize-=5;
        }
        if(type&HUMIDITY){
            buffersize-=5;
        }
        if(type&PRESSURE){
            buffersize-=5;
        }
        if(type&LUX){
            buffersize-=5;
        }
        if(type&UV){
            buffersize-=3;
        }
        if(type&IR){
            buffersize-=3;
        }
}

void SensorData::set(int index , uint8_t value){
    buffer[index] = value;
}
void SensorData::set(int index , uint16_t value){
    memcpy(&buffer[index], &value, sizeof(uint16_t));
}

void SensorData::set(int index , uint32_t value){
    memcpy(&buffer[index], &value, sizeof(uint32_t));
}

void SensorData::set(int index , int value){
    memcpy(&buffer[index], &value, sizeof(int));
}

uint16_t SensorData::getSize(){
    return buffersize;
}

uint8_t *SensorData::getBuffer(){
    return buffer;
}