#include "SensorServer.h"

// Constructeur de la classe SensorServer
SensorServer::SensorServer(MicroBit *ubit, MicroBitI2C *i2c, MicroBitPin *P0): SN(ubit->getSerial()){
    uBit = ubit;
    ID = 0;
    IDDst = 65535;
    this->i2c = i2c;
    this->P0 = P0;
}

// Destructeur de la classe SensorServer
SensorServer::~SensorServer(){
    free(sReader);
    free(display);
}

// Méthode pour initialiser le serveur
void SensorServer::init(){
    uBit->radio.enable(); 
    sReader = new SensorReader(uBit, i2c, TEMPERATURE|LUX|IR|PRESSURE|HUMIDITY|UV);
    display  = new Display(uBit, i2c, P0);
    InitConnection();
}

// Méthode pour initialiser la connexion avec le serveur 
void SensorServer::InitConnection(){
    if (state==0){
        display->setMessage("Initialisation connexion..");
        while(state==0){        
            RadioPacket packet;
            packet.setData((uint8_t *)SN.toCharArray(), SN.length());
            uBit->radio.datagram.send(packet.getPacketBuffer());
            uBit->sleep(10000);
        }
    } 
}

// Méthode principale permet d'afficher les données sur l'écran et de les envoyer au serveur
void SensorServer::run(){
  while(true){
        if(state == 1){
            display->clear();
            SensorData *data= sReader->read();
            display->setupScreen(data);
            display->render();
            sendData(data);
            uBit->sleep(5000);
        
        }     
    } 
}

// Méthode pour traiter les paquets reçus du serveur 
void SensorServer::receivepacket(){
    RadioPacket p (uBit->radio.datagram.recv(), ID);
    //uBit->display.scroll("REC");
    /* ManagedString str((char*)p.getDest());
    uBit->display.scroll(str); */

    if(!p.getErrorCode()){
        switch (p.getOpCode())
        {
        // Initialisation de la connexion
        case 0:
            if(state==0){
                uint8_t *data = p.getData();
                uint16_t size = p.getDataSize();
                int16_t snSize =SN.length();
                uint8_t displayOrderSize =0;
                uint8_t *displayorder;

                if (size>=snSize+2 && compare(data,(uint8_t *)SN.toCharArray(),snSize)){
                    memcpy(&ID,&data[snSize],sizeof(uint16_t));
                    
                    IDDst = p.getSource();

                    displayOrderSize = size-snSize-1;
                    displayorder = (uint8_t*)malloc(displayOrderSize);   
                    memcpy(displayorder,&data[snSize+1],(displayOrderSize));
                    sReader->setDisplayOrder(displayorder,displayOrderSize);
                    state = 1;
                    free(displayorder);
                }

            }
            break;
        //Mise à jour de l'ordre d'affichage suite à une demande de l'application traité par le serveur
        case 2 :
            if(state==1){
                uint8_t *data = p.getData();
                uint16_t size = p.getDataSize();
<<<<<<< HEAD
=======
>>>>>>> 93e9790368e3e1cea7c5b32b699e2fe0f5ed4646
                sReader->setDisplayOrder(data,size);
                state = 1;
            }
            break;
        default:
            break;
        }
    }

}

// Méthode pour envoyer les données au serveur
void SensorServer::sendData(SensorData *sData){
    RadioPacket packet;
    //uBit->display.scroll(ID);
    packet.setSource(ID);
    packet.setDest(IDDst);
    packet.setOpCode(1);
    packet.setData((uint8_t *)sData->getBuffer(), sData->getSize());
    uBit->radio.datagram.send(packet.getPacketBuffer());
} 

