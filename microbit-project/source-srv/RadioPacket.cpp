#include "RadioPacket.h"

RadioPacket::RadioPacket(PacketBuffer p){
    errornb=0;
    buffer = p;
    if(buffer.length()>9){
        opcode = p[0];
        idSource = (p[2]<<8)|p[1];
        idDest = (p[4]<<8)|p[3];
        dataSize = (p[6] << 8) | p[5];
        if(buffer.length()!=7+dataSize){
            setErrorCode(-2);
        }
        else{
            data = &p[7];
        }
    }
    else{
        setErrorCode(-1);
    }
}

RadioPacket::~RadioPacket(){}
uint16_t RadioPacket::getDataSize(){
    return dataSize;
}
uint8_t RadioPacket::getOpCode(){
    return opcode;
}

uint16_t RadioPacket::getSource(){
    return idSource;
}

uint16_t RadioPacket::getDest(){
    return idDest;
}

PacketBuffer *RadioPacket::getBuffer(){
    return &buffer;
}

ManagedString RadioPacket::getError(){
    switch (errornb)
    {
        case -1:
            return ManagedString("Erreur: taille buffer NOK");
            break;
        case -2:
            return ManagedString("Erreur: taille datasize NOK");
            break;
    default:
        return ManagedString("Erreur RadioPaquet");
        break;
    }
}

int RadioPacket::getErrorCode(){
    return errornb;
}

void RadioPacket::setErrorCode(int code){
    errornb = code;
}