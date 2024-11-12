#include "SerialPacket.h"

SerialPacket::SerialPacket(){
    opcode =0;
    data =NULL;
    datasize =0;
}

SerialPacket::SerialPacket(MicroBit *uBit, uint8_t *buffer, int length){
    errornb=0;
    data = NULL;
    opcode =99;
    if(length>2){
        opcode = buffer[0]-48;
        uBit->display.scroll(opcode);
        setData(&buffer[1], length-4);
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