#include "server.h"
#include "RadioPacket.h"

Server::Server(MicroBit *ubit, uint16_t id):uBit(ubit),serialServer(ubit){
    ID = id;
    uBit->radio.enable();
    uBit->init();
    serialServer.sendString("initialisation serveur OK");
}

Server::~Server(){

}

void Server::run(){
    while(1){
        uBit->sleep(1000);
    }
}

void Server::receivePacket(){
    RadioPacket p (uBit->radio.datagram.recv(), ID);
    if(p.getErrorCode()){
        serialServer.sendString(p.getError());
        serialServer.sendString(*p.getBuffer());
        serialServer.sendString(p.getDataSize());
    }
    else{
        serialServer.sendString(*p.getBuffer());
    }
}
