
#include "RadioServer.h"

MicroBit    uBit;
RadioServer rserv(&uBit, 65534);
SerialServer sserv(&uBit);

void onRadioDataReceive(MicroBitEvent){
    rserv.receivePacket();
}

void onSerialDataReceive(MicroBitEvent){
    sserv.receiveData();
}

int main()
{
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRadioDataReceive);
    uBit.radio.enable();
    rserv.init(&sserv);
    sserv.init(&rserv);
    rserv.run();
}
