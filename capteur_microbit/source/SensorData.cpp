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

// Récupère les types de mesures
MeasureType SensorData::getTypes(){
    return measuredtypes;
}

// Définit l'ordre d'affichage des mesures
void SensorData::setDisplayOrder(uint8_t* order, int size){
    // Initialisation de l'ordre d'affichage
    MeasureType temp = (MeasureType)0;

    // Parcours de l'ordre d'affichage
    for(uint8_t i=0; i<size; i++) {
        switch (order[i]) {
            case 'T': 
                temp = temp | TEMPERATURE;
                this->order[0] = i;
                break;
            case 'P': 
                temp = temp | PRESSURE;
                this->order[1] = i;
                break;
            case 'H': 
                temp = temp | HUMIDITY;
                this->order[2] = i;
                break;
            case 'L': 
                temp = temp | LUX;
                this->order[3] = i;
                break;
            case 'U': 
                temp = temp | UV;
                this->order[4] = i;
                break;
            case 'I': 
                temp = temp | IR;
                this->order[5] = i;
                break;
        }
    }
    //met à jour les types de mesures
    setTypes(temp);
}

// Définit les types de mesures
void SensorData::setTypes(MeasureType type){
    buffersize = 0;
    measuredtypes = type;
    
    //attribue la taille du buffer en fonction des types de mesures
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

// Définit la valeur d'un élément du buffer
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

// Récupère l'ordre d'affichage des mesures pour un type donéne
uint8_t SensorData::getOrder(MeasureType index){
    //
    switch(index){
        case TEMPERATURE:
            return order[0];
        case PRESSURE:
            return order[1];
        case HUMIDITY:
            return order[2];
        case LUX:
            return order[3];
        case UV:
            return order[4];
        case IR:
            return order[5];
        default:
            return 0;
    }
}

// Récupère la taille du buffer
uint16_t SensorData::getSize(){
    return buffersize;
}

//rrcupère le buffer
uint8_t *SensorData::getBuffer(){
    return buffer;
} 


