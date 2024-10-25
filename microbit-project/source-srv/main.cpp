#include "server.h"
MicroBit    uBit;
Server serv(&uBit);

void onDataReceive(MicroBitEvent){
    serv.receivePacket();
}

int main()
{
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onDataReceive);
    serv.run();
}
