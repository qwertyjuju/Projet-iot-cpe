#include "MicroBit.h"

MicroBit    uBit;

void onData(MicroBitEvent e)
{
    PacketBuffer p = uBit.radio.datagram.recv();

    if (p[0] == 1)
    {
        //uBit.io.P0.setServoValue(0);
        uBit.display.print("A");
    }

    if (p[0] == 2)
    {
        //uBit.io.P0.setServoValue(180);
        uBit.display.print("B");
    }
}

int main()
{
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();
    while(1)
        uBit.sleep(1000);
}
