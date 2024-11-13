#pragma once
#include "MicroBit.h"
//#include <openssl/aes.h>

class RadioPacket{
    /*
    Classe pour un paquet envoyé en Radio. en reception, on utilise directement le constructeur avec un packetBuffer,
    En envoi, le paquet est initialisé pour un envoit d'initialisation.
    */
    public: 

        /*
        *   Constructeur par défaut pour l'envoi d'un paquet
        */
        RadioPacket();
        /*
        *   Constructeur pour la reception d'un paquet. genère une erreur si la destination n'est pas égale à idserv
        */
        RadioPacket(PacketBuffer p, uint16_t idserv);
        ~RadioPacket();

        /*
        *   Retourne le numéro d'erreur si il y en a une
        */
        int getErrorCode();


        /*
        *   Retourne un message d'erreur en fonction du numéro d'erreur
        */
        ManagedString getError();

        // Getters
        uint8_t getOpCode();
        uint16_t getSource();
        uint16_t getDest();
        uint8_t *getData();
        PacketBuffer getPacketBuffer();
        uint16_t getDataSize();

        //setters
        void setOpCode(uint8_t opcode);
        void setSource(uint16_t source);
        void setDest(uint16_t dest);
        void setData(uint8_t *src, int size);

        bool isBroadcast();

        //encryption, Decryption
        void encrypt();
        void decrypt();
    
    private:
        void setErrorCode(int code);
        bool broadcast;
        int bufferSize;
        uint16_t idServ;
        uint8_t opcode;
        uint16_t idSource;
        uint16_t idDest;
        uint16_t dataSize;
        uint8_t *data;
        uint16_t* checksum;
        int errornb;
};