#include "RadioPacket.h"

RadioPacket::RadioPacket(){
    data = NULL;
    dataSize=0;
    idServ=0;
    idSource =0;
    idDest=65535;
    opcode=0;
    bufferSize = 9;
    pbuffer = NULL;

}
RadioPacket::RadioPacket(PacketBuffer *p, uint16_t idserv){
    idServ = idserv;
    errornb=0;
    pbuffer = p;
    bufferSize = pbuffer->length();
    if(bufferSize>9){
        opcode = (*p)[0];
        idSource = ((*p)[2]<<8)|(*p)[1];
        idDest = ((*p)[4]<<8)|(*p)[3];
        if(idDest != idServ){
            setErrorCode(-3);
            return;
        }
        dataSize = ((*p)[6] << 8) | (*p)[5];
        if(bufferSize!=9+dataSize){
            setErrorCode(-2);
            return;
        }
        else{
            data = &(*p)[7];
        }
    }
    else{
        setErrorCode(-1);
        return;
    }
}

RadioPacket::~RadioPacket(){
    free(data);
}

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


void RadioPacket::setOpCode(uint8_t opcode){
    this->opcode = opcode;

}
void RadioPacket::setSource(uint16_t source){
    idSource = source;
}
void RadioPacket::setDest(uint16_t dest){
    idDest = dest;
}

void RadioPacket::setData(uint8_t *src, int size){
    data = (uint8_t*)malloc(size);
    memcpy(data, src, size);
}

PacketBuffer* RadioPacket::getPacketBuffer(){
    if(pbuffer==NULL){
        pbuffer = new PacketBuffer(bufferSize+dataSize);
        uint8_t * buffer = pbuffer->getBytes();
        memcpy(&buffer[0], &opcode,sizeof(uint8_t));
    }
    return pbuffer;
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
        case -3:
            return ManagedString("Erreur: ID Destination NOK");
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


void RadioPacket::decrypt(){
    
}