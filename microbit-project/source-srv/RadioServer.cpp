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
    PacketBuffer pb = uBit->radio.datagram.recv();
    RadioPacket p (&pb, ID);
    if(p.getErrorCode()){
        serialServer->sendString(p.getError());
        serialServer->sendString(*p.getPacketBuffer());
        serialServer->sendString(p.getDataSize());
        serialServer->sendString(p.getSource());
        serialServer->sendString(p.getDest());
    }
    else{
        switch(p.getOpCode()){
            case 0:
                serialServer->sendString(*p.getPacketBuffer());
                serialServer->sendString(p.getDataSize());
                break;
        }
    }
}
