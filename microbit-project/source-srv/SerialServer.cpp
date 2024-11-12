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
    ManagedString ms = uBit->serial.readUntil("EOT\n");
    uBit->display.scroll(ms.toCharArray()[0]);
    SerialPacket p(uBit, (uint8_t*)ms.toCharArray(), ms.length());
    sendMessage({(char*)p.getData(), (int16_t)p.getDataSize()});
    if(!p.getErrorCode()){
        radioServer->processSerialPacket(&p);
    }
}


void SerialServer::sendPacket(SerialPacket *p){
    uint8_t code= p->getOpCode();
    uBit->serial.send(&code, 1);
    uBit->serial.send(p->getData(), p->getDataSize());
    uBit->serial.send("EOT\n");
}
void SerialServer::sendMessage(ManagedString str){
    SerialPacket p;
    p.setOpCode(255);
    p.setData((uint8_t*)str.toCharArray(), str.length());
    sendPacket(&p);
}