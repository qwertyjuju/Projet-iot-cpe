#include "SensorServer.h"

SensorServer::SensorServer(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *P0): SN(ubit->getSerial()){
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
    InitConnection();
}
void SensorServer::InitConnection(){
    if (state==0){
        while(state==0){        
            RadioPacket packet;
            packet.setData((uint8_t *)SN.toCharArray(), SN.length());
            uBit->radio.datagram.send(*packet.getPacketBuffer());
            uBit->sleep(3000);
        }
    } 
}
void SensorServer::run(){
  while(true){
        if(state == 1){
        SensorData *data= sReader->read();
        display->setupScreen(data);
        display->render();
        sendPacket(data);
        uBit->sleep(5000);
        }
     
    } 
}

void SensorServer::receivepacket(){
    PacketBuffer pb = uBit->radio.datagram.recv();
    RadioPacket p (&pb, ID);
    if(!p.getErrorCode()){
        switch (p.getOpCode())
        {
        case 0:
            if(state==0){
                uint8_t *data = p.getData();
                uint16_t size = p.getDataSize();
                int16_t snSize =SN.length();
                if (size==snSize+4 && compare(data,(uint8_t *)SN.toCharArray(),snSize)){
                    memcpy(&ID,&data[snSize-1],sizeof(uint16_t));
                    state = 1;
                }
            }
        case 1 :
            if(state==1){
                uint8_t *data = p.getData();
                uint16_t size = p.getDataSize();
                uint16_t snSize =SN.length();
                if(size>=snSize+4 ){
                }
            }
            break;
        
        default:
            break;
        }
    }
}

void SensorServer::sendPacket(SensorData *sData){
    RadioPacket packet;
    packet.setData((uint8_t *)sData->getBuffer(), sData->getSize());
    uBit->radio.datagram.send(*packet.getPacketBuffer());
} 

