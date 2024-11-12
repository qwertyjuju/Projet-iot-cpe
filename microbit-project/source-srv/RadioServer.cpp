#include "RadioServer.h"


RadioServer::RadioServer(MicroBit *ubit, uint16_t id):uBit(ubit){
    ID = id;
}

RadioServer::~RadioServer(){

}

void RadioServer::run(){
    while(1){
        serialServer->receiveData();
        uBit->sleep(3000);
    }
}

void RadioServer::init(SerialServer *serv){
    serialServer = serv;
    if(serialServer)
        serialServer->sendMessage("initialisation serveur OK");
}

void RadioServer::receivePacket(){
    RadioPacket rp(uBit->radio.datagram.recv(), ID);
    SerialPacket sp;
    if(!rp.getErrorCode()){
        switch(rp.getOpCode()){
            case 0:
                sp.setData(rp.getData(), rp.getDataSize());
                serialServer->sendPacket(&sp);
                break;
            case 1:
                sp.setOpCode(1);
                sp.setData(rp.getData(), rp.getDataSize());
                serialServer->sendPacket(&sp);
                break;
        }
    }
    else{
        serialServer->sendMessage(rp.getError());
    }
    /*
    uint16_t src =0x0001;
    uint8_t buffer[16]={0};
    char test[4]= {'L', 'U', 'T', 'H'};
    if(!rp.getErrorCode()){
        switch(rp.getOpCode()){
            case 0:
                serialServer->sendMessage(rp.getSource());
                resp.setSource(ID);
                resp.setDest(0);
                memcpy(buffer, (uint8_t*)rp.getData(), 10);
                memcpy(&buffer[10], (uint8_t*)&src, 2);
                memcpy(&buffer[12], (uint8_t*)test, 4);
                resp.setData(buffer, 16);
                uBit->radio.datagram.send(resp.getPacketBuffer());
                break;
            case 1:
                serialServer->sendMessage(rp.getSource());
                break;
        }
    }
    else{
        serialServer->sendMessage(rp.getError());
    }*/
}

void RadioServer::processSerialPacket(SerialPacket p){
    RadioPacket rp;
    uint8_t opcode = p.getOpCode();
    switch(opcode){
        case 0:
            rp.setSource(ID);
            rp.setDest(0);
            rp.setOpCode(p.getOpCode());
            rp.setData(p.getData(), p.getDataSize());
            uBit->radio.datagram.send(rp.getPacketBuffer());
    }


}
