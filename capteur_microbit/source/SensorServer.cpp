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
void SensorServer::InitConnection(){
    if (state==0){
        while(state==0){        
            RadioPacket packet;
            packet.setData((uint8_t *)SN.toCharArray(), SN.length());
            uBit->radio.datagram.send(*packet.getPacketBuffer());
            uBit->sleep(5000);
        }
    }

    
}
void SensorServer::run(){
    while(true){
        SensorData *data= sReader->read();
        display->setupScreen(data);
        display->render();
        uBit->sleep(100);
    }
}

void SensorServer::receivepacket(MicroBitEvent){
    PacketBuffer pb = uBit->radio.datagram.recv();
    RadioPacket p (&pb, ID);
    if(!p.getErrorCode()){
        switch (state)
        {
        case 0:
            if(p.getOpCode()==0){
                uint8_t *data = p.getData();
                uint16_t size = p.getDataSize();
                int16_t snSize =SN.length();
                if (size==snSize+2 && compare(data,(uint8_t *)SN.toCharArray(),snSize)){
                    memcpy(&ID,&data[snSize-1],sizeof(uint16_t));
                }
            }
            break;
        default:
            break;
        }
    }
}

