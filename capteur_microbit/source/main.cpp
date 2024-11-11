#include "MicroBit.h"
#include "SensorServer.h"

MicroBit uBit;   
MicroBitI2C i2c(I2C_SDA0,I2C_SCL0);
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL_OUT);
SensorServer server(&uBit,&i2c, &P0);

void onRadioDataReceive(MicroBitEvent)
{
    //uBit.display.scroll("RECEIVE");
    server.receivepacket();
}

int main()
{
    //uBit.display.scroll("START");
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRadioDataReceive);
    server.init();
    //uBit.display.scroll("run");
    server.run();   
    release_fiber();
}


