#include "server.h"

Server::Server(MicroBit *ubit):serialServer(ubit){
    uBit = ubit;
    //uBit->messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onDataReceive);
    uBit->messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, this, &Server::receivePacket, MESSAGE_BUS_LISTENER_DROP_IF_BUSY);
    uBit->radio.enable();
    serialServer.sendString("initialisation serveur OK");
}

Server::~Server(){

}

void Server::run(){
    while(1){
        uBit->display.print(1);
        serialServer.sendString("UP!");
        uBit->sleep(1000);
    }
}

void Server::receivePacket(MicroBitEvent){
    //uBit->display.scroll(2);
    serialServer.sendString("RECEIVE");
}
