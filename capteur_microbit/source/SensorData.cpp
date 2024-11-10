#include "SensorData.h"

SensorData::SensorData( MeasureType type){
    this->buffersize= 0;
    this->setTypes(type);
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
MeasureType SensorData::getTypes(){
    return measuredtypes;
}

void SensorData::setTypes(uint8_t *buffer, int length){
    measuredtypes = (MeasureType)0;
    for(int i=0; i<length; i++){
        measuredtypes =  measuredtypes|(MeasureType)buffer[i];
    }
}

void SensorData::displayOrder(){
    for(int i=0; i<6; i++){
        this->order[i] = ;
    }
}
void SensorData::setTypes(MeasureType type){
    buffersize = 0;
    measuredtypes = type;
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