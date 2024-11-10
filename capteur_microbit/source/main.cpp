#include "MicroBit.h"
#include "SensorServer.h"

MicroBit uBit;   
MicroBitI2C i2c(I2C_SDA0,I2C_SCL0);
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL_OUT);
SensorServer server(&uBit,&i2c, &P0);



int main()
{
    server.init();
    server.run();
    release_fiber();
}


