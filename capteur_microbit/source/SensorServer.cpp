#include "SensorServer.h"


SensorServer::SensorServer(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *P0): sReader(ubit, i2c, TEMPERATURE|LUX|IR|PRESSURE|HUMIDITY|UV), display(ubit, i2c, P0){
    uBit = ubit;
    uBit->radio.enable();
    ID = 0;
}

SensorServer::~SensorServer(){

}

void SensorServer::run(){
    while(true){
        display.setupScreen(sReader.read());
        display.render();
        uBit->sleep(100);
    }
}

