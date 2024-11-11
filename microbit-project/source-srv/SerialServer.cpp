#include "SerialServer.h"

SerialServer::SerialServer(MicroBit *ubit){
    uBit = ubit;
    //uBit->serial.eventOn("EOT\n");
}

SerialServer::~SerialServer(){

}

void SerialServer::init(RadioServer *serv){
    radioServer = serv;
}


void SerialServer::receiveData(){
    uBit->serial.readUntil("EOT\n");
}


void SerialServer::sendPacket(SerialPacket *p){
    uBit->serial.send(p->getBuffer(), p->getSize());
    uBit->serial.send("EOT\n");
}
void SerialServer::sendMessage(ManagedString str){
    SerialPacket p;
    p.setOpCode(255);
    p.setData((uint8_t*)str.toCharArray(), str.length());
    sendPacket(&p);
}