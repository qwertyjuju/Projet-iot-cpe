#include "server.h"
#include <openssl/aes.h>
MicroBit    uBit;
Server serv(&uBit, 65534);

void onDataReceive(MicroBitEvent){
    serv.receivePacket();
}

int main()
{
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onDataReceive);
    serv.run();
}
