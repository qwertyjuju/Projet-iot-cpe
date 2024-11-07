#include "SensorDataContainer.h"

SensorDataContainer::SensorDataContainer(MeasureType type){
    this->type = type;
    this->first = NULL;
    switch(this->type){
        case TEMPERATURE:
            addData(TEMPERATURE);
    }
    
}

void SensorDataContainer::addData(MeasureType type){
    if (first==NULL){
        first = new SensorData();
    }else{
        SensorData *temp = first;
        first = new SensorData()
    } 
}
SensorDataContainer::~SensorDataContainer(){

}