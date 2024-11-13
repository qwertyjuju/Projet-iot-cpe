#pragma once
#include "MicroBit.h"

class SerialPacket{
    /*
    *   Classe pour l'envoie et la reception d'un paquet sur le port serie:    * 
    */
    public:
        /*
        *   Constructeur pour l'envoi des données. Par défaut créer un paquet avec l'opcode 0 (message d'initialisation)
        */
        SerialPacket();
        /*
        *   Constructeur pour la réception des données
        */
        SerialPacket(uint8_t *buffer, int length);
        ~SerialPacket();

        /* 
        *   copie des données à envoyer
        */
        void setData(uint8_t* buffer, int datasize);
        /*
        *   Attribution opcode:
        *   0: envoie/reception d'un message d'initialisation d'un microbit capteur
        *   1: envoie des données reçues par un capteur
        *   2: reception d'un paquet de changement de display order
        *   255: envoie d'un message de logs
        */
        void setOpCode(uint8_t code);
        
        /*
        *   Retourne les données du paquets
        */
        uint8_t *getData(); 

        /*
        *
        *   Renvois la taille du buffer de données
        */
        uint16_t getDataSize();

        /*
        *   Retourne le numéro d'erreur si il y en a une
        */
        int getErrorCode();
        
        /*
        *   Attribue un numéro d'erreur
        */
        void setErrorCode(int code);

        /*
        *   Retourne un message d'erreur en fonction du numéro d'erreur
        */
        ManagedString getError();

        /*
        *   Retourne l'opcode
        */
        uint8_t getOpCode();


    private:
        uint8_t opcode;
        uint8_t *data;
        uint8_t *buffer;
        uint16_t datasize;
        int errornb;
};