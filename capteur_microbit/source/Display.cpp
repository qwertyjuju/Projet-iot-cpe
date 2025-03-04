#include "Display.h"

Display::Display(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *pin): screen(ubit, i2c, pin){

}

Display::~Display(){

}

void Display::init( ){

}
// Méthode pour afficher un message sur l'écran
void Display::setMessage(ManagedString string){
    screen.display_line(0, 0, string.toCharArray());
    screen.update_screen();
}

// Méthode pour effacer le contenu de l'écran
void Display::clear(){
    char empty[50] ;
    memset(empty, ' ', 50);
    screen.display_line(0, 0, empty);
    screen.update_screen();
}

// Méthode pour afficher les données sur l'écran en fonction du type de mesure
void Display::setupScreen(SensorData *data){
    int i = 0;
    uint8_t * buffer = data->getBuffer();

    while(i<data->getSize()){

        MeasureType type = (MeasureType)buffer[i];

        if(type == TEMPERATURE){
            int temp =0;
            memcpy(&temp, &buffer[i+1], sizeof(int));
            ManagedString displayTemp = "Temp:" + ManagedString(temp / 100) + "." + (temp > 0 ? ManagedString(temp % 100) : ManagedString((-temp) % 100)) + " C";
            screen.display_line(data->getOrder(type), 0, displayTemp.toCharArray());
            i+=5;
        }
        if(type == HUMIDITY){
            int hum =0;
            memcpy(&hum, &buffer[i+1], sizeof(int));
            ManagedString displayHumi = "Humi:" + ManagedString(hum / 100) + "." + ManagedString(hum % 100) + " rH";
            screen.display_line(data->getOrder(type), 0, displayHumi.toCharArray());
            i+=5;
        }
        if(type == PRESSURE){
            int pres =0;
            memcpy(&pres, &buffer[i+1], sizeof(int));
            ManagedString displayPres = "Pres:" + ManagedString(pres) + " hPa";
            screen.display_line(data->getOrder(type), 0, displayPres.toCharArray());
            i+=5;
        }
        if(type == LUX){
            uint32_t lux =0;
            memcpy(&lux, &buffer[i+1], sizeof(uint32_t));
            ManagedString displayLux = "Lux:" + ManagedString((int)lux);
            screen.display_line(data->getOrder(type), 0, displayLux.toCharArray());
            i+=5;
        }
        if(type == UV){
            uint16_t uv =0;
            memcpy(&uv, &buffer[i+1], sizeof(uint16_t));
            ManagedString displayUV = "UV:" + ManagedString(uv);
            screen.display_line(data->getOrder(type), 0, displayUV.toCharArray());
            i+=3;
        }
        if(type == IR){
            uint16_t ir =0;
            memcpy(&ir, &buffer[i+1], sizeof(uint16_t));
            ManagedString displayIR = "IR:" + ManagedString((int)ir);
            screen.display_line(data->getOrder(type), 0, displayIR.toCharArray());
            i+=3;
        }
    }
} 

// Méthode pour mettre à jour l'écran
void Display::render(){
    screen.update_screen();
}