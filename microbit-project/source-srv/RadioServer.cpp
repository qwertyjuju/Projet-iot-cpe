#include "RadioServer.h"
#include "RadioPacket.h"

RadioServer::RadioServer(MicroBit *ubit, uint16_t id):uBit(ubit){
    ID = id;
    uBit->radio.enable();
}

RadioServer::~RadioServer(){

}

void RadioServer::run(){
    while(1){
        uBit->sleep(1000);
    }
}

void RadioServer::init(SerialServer *serv){
    serialServer = serv;
    if(serialServer)
        serialServer->sendString("initialisation serveur OK");
}

void RadioServer::receivePacket(){
    RadioPacket p (&uBit->radio.datagram.recv(), ID);
    if(p.getErrorCode()){
        serialServer->sendString(p.getError());
        serialServer->sendString(*p.getBuffer());
        serialServer->sendString(p.getDataSize());
    }
    else{
        switch(p.getOpCode()){
            case 0:
                break;
        }
    }
}
