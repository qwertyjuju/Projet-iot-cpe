#include "server.h"

MicroBit    uBit;
int main()
{
    uBit.init();
    Server serv(&uBit);
    serv.run();
}
