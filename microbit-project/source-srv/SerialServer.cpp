#include "SerialServer.h"

SerialServer::SerialServer(MicroBit *ubit){
    uBit = ubit;
}

SerialServer::~SerialServer(){

}

void SerialServer::sendString(ManagedString str){
    uBit->serial.send(str);
    uBit->serial.send("EOT\n");
}