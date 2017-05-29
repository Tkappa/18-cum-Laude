//
// Created by Igor Ershov on 05/04/2017.
//

#ifndef MAPPA_MAPPA_H
#define MAPPA_MAPPA_H
#include <list>
#include "Stanza.h"
#include "../../model/pc/Character.hpp"
struct posizione{
int mapX,mapY,stanzX,stanzY;
};

struct pers{
char nome;
posizione pos;
};

typedef pers* p_pers;
typedef Character* p_char;
const int altezzaMappa=3,lunghezzaMappa=16;
class Mappa{
    protected:
        Stanza mappa[altezzaMappa][lunghezzaMappa];
        pers scalasu;
        pers scalagiu;
        std::list<p_char> Oggetti;
    public:
        //crea una nuova mappa popolata da stanza
        Mappa(int nLivelliPrec);
//        Mappa(const Mappa& orig);
        //stampa la mappa con cout facendo solo 0 e 1
        void stampaMappa();
        //restituisce il carattere che sta alle coordinate specificate
        char getMapChar(int MapX,int MapY,int StX,int StY);
        //scrive sulla struttura dati di personaggio e lo sposta nella direzione specificata
        void moveChar(Character & personaggio,int dir);
        //mette il personaggio specificato(dovrebbe essere quello principale) sopra le scale che portano su come posizione iniziale
        void assegnaPosIniziale(Character &personaggio);
        //assegna la posizione specificata al personaggio passato per paramentro
        void assegnaPos(Character &personaggio,int MapX,int MapY,int StX,int StY);
        //Inserisce nella struttura dati l'oggetto passato
        void nuovoOggetto(Character oggetto);
        //ritorna vero se il personaggio inserito pu� muoversi nella direzione specificata , altimenti falso
        bool mapCanMove(Character & personaggio,int dir);
        //ritorna il valore di "esplorato" della stanza in quelle coordinate
        bool stanzaEsplorata(int MapX,int MapY);
        //fornisce una copia di "oggetti"
        std::list<p_char> getList();

};


#endif //MAPPA_MAPPA_H
