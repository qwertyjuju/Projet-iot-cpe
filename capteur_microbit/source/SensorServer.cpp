#include "SensorServer.h"


SensorServer::SensorServer(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *P0): sReader(ubit, i2c, TEMPERATURE|LUX|IR|PRESSURE|HUMIDITY|UV), display(ubit, i2c, P0), SN(uBit->getSerial()){
    uBit = ubit;
    ID = 0;
    state = 0;
    uBit->radio.enable();
    InitConnection();
}

SensorServer::~SensorServer(){

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
        SensorData *data= sReader.read();
        display.setupScreen(data);
        display.render();
        uBit->sleep(100);
    }
}

void SensorServer::receivepacket(MicroBitEvent){
    RadioPacket p (&uBit->radio.datagram.recv(), ID);
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

