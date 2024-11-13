
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
    uBit.init();    //  initialisation microbit
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRadioDataReceive);// appel de la methode receivePacket du serveur lors de la reception d'un message radion
    uBit.radio.enable();
    rserv.init(&sserv);//   Initialisation serveur radio
    sserv.init(&rserv);// Initialisation serveur serie
    rserv.run();// Boucle de lecture serie
}
