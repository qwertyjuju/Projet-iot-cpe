#pragma once
#include "MicroBit.h"
#include "SerialServer.h"
#include "RadioPacket.h"
#include "SerialPacket.h"

class SerialServer;

class RadioServer{

    /*
    Classe principale pour la passerelle recevant les données.
    */
    public:
        /*
        *   Constructeur 
        */
        RadioServer(MicroBit *ubit, uint16_t id);
        ~RadioServer();
        void init(SerialServer *serv);
        /*
        *   Méthode gérant la réception de paquets radio
        */
        void receivePacket();
        /*
        *   Méthode principale. Boucle sur la reception des données serie
        */
        void run();

        /*
        *   Méthode gérant la reception d'un paquet serie et communique avec les 
        *   microbit capteur en fonction de l'opcode
        */
        void processSerialPacket(SerialPacket *p);
        
    private:
        uint16_t ID;
        MicroBit *uBit;
        SerialServer *serialServer;
};