#include "SerialPacket.h"

SerialPacket::SerialPacket(){
    opcode =0;
    data =NULL;
    datasize =0;
}

SerialPacket::SerialPacket(ManagedString str){
    uint8_t *tbuffer = (uint8_t*)str.toCharArray();
    data = NULL;
    if(str.length()>2){
        opcode = tbuffer[0];
        setData(&tbuffer[1], str.length()-1);
    }else{
        setErrorCode(-1);
    }
}


SerialPacket::~SerialPacket(){
    free(data);
}

void SerialPacket::setOpCode(uint8_t code){
    opcode = code;
}
void SerialPacket::setData(uint8_t* buffer, int size){
    datasize = size;
    data = (uint8_t *)malloc(datasize);
    memcpy(data, buffer, datasize);
}
uint16_t SerialPacket::getDataSize(){
    return datasize;
}

uint8_t *SerialPacket::getData(){
    return data;
}

void SerialPacket::setErrorCode(int code){
    errornb =code;
}

int SerialPacket::getErrorCode(){
    return errornb;
}
uint8_t SerialPacket::getOpCode(){
    return opcode;
}

ManagedString SerialPacket::getError(){
    switch (errornb)
    {
        case -1:
            return ManagedString("Erreur: taille NOK");
            break;
    default:
        return ManagedString("Erreur SerialPacket");
        break;
    }
}