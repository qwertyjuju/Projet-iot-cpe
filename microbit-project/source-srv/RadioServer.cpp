#include "RadioServer.h"
#include "RadioPacket.h"

RadioServer::RadioServer(MicroBit *ubit, uint16_t id):uBit(ubit){
    ID = id;
}

RadioServer::~RadioServer(){

}

void RadioServer::run(){
    while(1){
        serialServer->receiveData();
        uBit->sleep(1000);
    }
}

void RadioServer::init(SerialServer *serv){
    serialServer = serv;
    if(serialServer)
        serialServer->sendMessage("initialisation serveur OK");
}

void RadioServer::receivePacket(){
    PacketBuffer pb = uBit->radio.datagram.recv();
    RadioPacket rp(pb, ID);
    uBit->display.scroll(rp.getDataSize());
    RadioPacket resp;
    SerialPacket sp;
    uint16_t src =1;
    uint8_t buffer[16]={0};
    char test[4]= {'L', 'U', 'T', 'H'};
    if(!rp.getErrorCode()){
        switch(rp.getOpCode()){
            case 0:
                serialServer->sendMessage(pb);
                resp.setSource(ID);
                resp.setDest(0);
                memcpy(buffer, (uint8_t*)rp.getData(), 10);
                memcpy(&buffer[10], (uint8_t*)&src, 2);
                memcpy(&buffer[12], (uint8_t*)test, 4);
                resp.setData(buffer, 16);
                uBit->radio.datagram.send(resp.getPacketBuffer());
                break;
            case 1:
                serialServer->sendMessage(rp.getPacketBuffer());
                break;
        }
    }
    else{
        serialServer->sendMessage(rp.getError());
    }
}
