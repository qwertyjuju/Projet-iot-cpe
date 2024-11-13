#include "RadioPacket.h"

/* Constructeur par défaut de la classe RadioPacket. 
Initialise les membres à des valeurs par défaut.*/
RadioPacket::RadioPacket(){
    data = NULL; //taille vaiable
    dataSize=0; //2octets
    idServ=0; 
    idSource =0; //2octets
    idDest=65535; //2octets
    opcode=0; //1octet
    bufferSize = 9; //init à 9 car cest la taille des éléments permanents à chaque message
    checksum = 0; //2octets
}

// Constructeur de la classe RadioPacket pour créer un paquet radio à partir d'un buffer
RadioPacket::RadioPacket(PacketBuffer p, uint16_t idserv){
    idServ = idserv;
    errornb=0;
    uint8_t *buffer =  p.getBytes();
    bufferSize = p.length();

    // Vérification qu'on a bien reçu un paquet complet
    if(bufferSize>9){
        opcode = buffer[0];
        idSource = (buffer[2]<<8)|buffer[1];
        idDest = (buffer[4]<<8)|buffer[3];
        // Vérification qu'il s(agit bien du mcirobit avec qui on s'était init
        if(idDest != 65535){
            broadcast = false;
            if(idDest != idServ){
                setErrorCode(-3);
            }
        }else{
            broadcast = true;
        }
        dataSize = (buffer[6] << 8) | buffer[5];
        // Vérification de la taille du buffer
        if(bufferSize!=9+dataSize){
            setErrorCode(-2);
        }

        // Vérification de la taille des donnéées
        if (dataSize>=255){
            setErrorCode(-4);
        }
        else{
            data = (uint8_t*) malloc(dataSize);
            memcpy(data,&buffer[7],dataSize);
        }
    }
    else{
        // Erreur de taille de buffer
        setErrorCode(-1);
        return;
    }
}

RadioPacket::~RadioPacket(){
    free(data);
}

uint8_t *RadioPacket::getData(){
    return data;
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

bool RadioPacket::isBroadcast(){
    return broadcast;
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
    dataSize = size;
}

// Méthode pour obtenir le buffer du paquet radio
PacketBuffer RadioPacket::getPacketBuffer(){
    PacketBuffer pbuffer(bufferSize+dataSize);
    uint8_t * buffer = pbuffer.getBytes();
    memcpy(&buffer[0], &opcode,sizeof(uint8_t));
    memcpy(&buffer[1], &idSource,sizeof(uint16_t));
    memcpy(&buffer[3], &idDest,sizeof(uint16_t));
    memcpy(&buffer[5], &dataSize,sizeof(uint16_t));
    memcpy(&buffer[7], data, dataSize);
    memcpy(&buffer[7+dataSize], checksum, sizeof(uint16_t));
    return pbuffer;
}

// Méthode pour gerer le message d'erreur
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
        case -4:
            return ManagedString("Erreur: Taille data trop importante");
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