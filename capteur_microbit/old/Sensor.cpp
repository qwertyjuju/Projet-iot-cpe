#include "Sensor.h"

Sensor::Sensor(SensorDevice device){
    this->device = device;
    active=false;
}

Sensor::~Sensor(){

}
Sensor::read(){
    
}

void Sensor::activate(){
    active = true;
}
bool Sensor::isActive(){
    return active;
}