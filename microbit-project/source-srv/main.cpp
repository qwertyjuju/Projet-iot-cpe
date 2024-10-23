#include "MicroBit.h"

MicroBit    uBit;

void onData(MicroBitEvent e)
{
    PacketBuffer p = uBit.radio.datagram.recv();
}

int main()
{
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();
    while(1)
        uBit.sleep(1000);
}
