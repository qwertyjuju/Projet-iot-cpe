#include "RadioServer.h"


RadioServer::RadioServer(MicroBit *ubit, uint16_t id):uBit(ubit){
    ID = id;
}

RadioServer::~RadioServer(){

}

void RadioServer::run(){
    while(1){
        serialServer->receiveData();
    }
}

void RadioServer::init(SerialServer *serv){
    serialServer = serv;
    if(serialServer)
        serialServer->sendMessage("initialisation serveur OK");
}

void RadioServer::receivePacket(){
    RadioPacket p(uBit->radio.datagram.recv(), ID);
    SerialPacket sp;
    if(!p.getErrorCode()){
        switch(p.getOpCode()){
            case 0:
                sp.setData(p.getData(), p.getDataSize());
                serialServer->sendPacket(&sp);
                break;
            case 1:
                sp.setOpCode(1);
                uint8_t *buffer = (uint8_t* )malloc(p.getDataSize()+2);
                uint16_t src = p.getSource();
                memcpy(buffer, &src,sizeof(uint16_t));
                memcpy(&buffer[2], p.getData(), p.getDataSize());
                sp.setData(buffer, p.getDataSize());
                serialServer->sendPacket(&sp);
                free(buffer);
                break;


        }
    }
    else{
        serialServer->sendMessage(p.getError());
    }

}

void RadioServer::processSerialPacket(SerialPacket *p){
    RadioPacket rp;
    uint8_t opcode = p->getOpCode();
    switch(opcode){
        case 0:
            rp.setSource(ID);
            rp.setDest(0);
            rp.setOpCode(p->getOpCode());
            rp.setData(p->getData(), p->getDataSize());
            uBit->radio.datagram.send(rp.getPacketBuffer());
            break;
        case 2:
            uint16_t dest;
            memcpy(&dest, p->getData(), sizeof(uint16_t));
            rp.setSource(ID);
            rp.setDest(dest);
            rp.setOpCode(p->getOpCode());
            rp.setData(p->getData(), p->getDataSize()-2);
            uBit->radio.datagram.send(rp.getPacketBuffer());
            break;
    }


}
