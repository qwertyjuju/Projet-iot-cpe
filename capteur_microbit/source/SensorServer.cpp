#include "SensorServer.h"


SensorServer::SensorServer(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *P0){
    uBit = ubit;
    ID = 0;
    this->i2c = i2c;
    this->P0 = P0;
}

SensorServer::~SensorServer(){
    free(sReader);
    free(display);
}

void SensorServer::init(){
    uBit->init();
    uBit->radio.enable();
    sReader = new SensorReader(uBit, i2c, TEMPERATURE|LUX|IR|PRESSURE|HUMIDITY|UV);
    display  = new Display(uBit, i2c, P0);
}

void SensorServer::run(){
    while (true)
    {
        //uBit->display.scroll("SensorServer");
        display->setupScreen(sReader->read());
        display->render();
        uBit->sleep(100);
    }
}

