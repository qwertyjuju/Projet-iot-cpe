#include "SerialServer.h"

SerialServer::SerialServer(MicroBit *ubit){
    uBit = ubit;
    uBit->serial.eventOn("EOT\n");
}

SerialServer::~SerialServer(){

}

void SerialServer::init(RadioServer *serv){
    radioServer = serv;
    sendString("Initiatialisation Serial Server OK");
}


void SerialServer::receiveData(){

}

void SerialServer::sendString(ManagedString str){
    uBit->serial.send(str);
    uBit->serial.send("EOT\n");
}