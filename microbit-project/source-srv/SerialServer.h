#pragma once
#include "MicroBit.h"
#include "RadioServer.h"
#include "SerialPacket.h"

class RadioServer;
class SerialServer{
    /*
    Classe pour le serveur gérant la partie communication série avec l'ordinateur
    */
    public:
        SerialServer(MicroBit *ubit);
        ~SerialServer();
        /*
        *   envoie d'un message pour les logs du serveur. L'opcode du message est directement mis
        *   à 255.
        */
        void sendMessage(ManagedString str);
        /*
        *   Initialistaion Serveur
        */ 
        void init(RadioServer *serv);
        /*
        *   Fonction a appelé pour la reception des donnée sur le port série
        */
        void receiveData();

        /*
        *
        *   Fonction d'envoi d'un paquet sur le port serie
        */
        void sendPacket(SerialPacket *p);

    private:
        MicroBit *uBit;
        RadioServer *radioServer;
};