#include "SerialPacket.h"

SerialPacket::SerialPacket(){
    opcode =0;
    data =NULL;
    size =0;
}

SerialPacket::~SerialPacket(){
    free(data);
}

void SerialPacket::setOpCode(uint8_t code){
    opcode = code;
}
void SerialPacket::setData(uint8_t* buffer, int datasize){
    size = datasize+1;
    data = (uint8_t *)malloc(size);
    memcpy(data, &opcode, 1);
    memcpy(&data[1], buffer, size-1);
}
uint16_t SerialPacket::getSize(){
    return size;
}

uint8_t *SerialPacket::getBuffer(){
    return data;
}