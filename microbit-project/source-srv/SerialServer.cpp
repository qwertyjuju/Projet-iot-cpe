#include "SerialServer.h"

SerialServer::SerialServer(MicroBit *ubit){
    uBit = ubit;
}

SerialServer::~SerialServer(){

}

void SerialServer::init(RadioServer *serv){
    radioServer = serv;
}


void SerialServer::receiveData(){
    ManagedString ms = uBit->serial.readUntil("\r\n");
    SerialPacket p((uint8_t*)ms.toCharArray(), ms.length());
    if(!p.getErrorCode()){
        radioServer->processSerialPacket(&p);
    }
}


void SerialServer::sendPacket(SerialPacket *p){
    uint8_t code= p->getOpCode();
    uBit->serial.send(&code, sizeof(uint8_t));
    uBit->serial.send(p->getData(), p->getDataSize());
    uBit->serial.send("EOT\n");
}
void SerialServer::sendMessage(ManagedString str){
    SerialPacket p;
    p.setOpCode(255);
    p.setData((uint8_t*)str.toCharArray(), str.length());
    sendPacket(&p);
}