//
// Created by Igor Ershov on 05/04/2017.
//

#ifndef MAPPA_MAPPA_H
#define MAPPA_MAPPA_H
#include <list>
#include "Stanza.h"
#include <queue>
#include "../../model/pc/Character.hpp"

struct pers{
char nome;
mapPos pos;
};
struct obj{
char nome;
mapPos pos;
};

typedef obj* p_obj;
typedef Character* p_char;
const int altezzaMappa=3,lunghezzaMappa=16;

class Mappa{
    protected:
        Stanza mappa[altezzaMappa][lunghezzaMappa];
        int nLevel;
        pers scalasu;
        pers scalagiu;
        int nRooms;
        std::list<p_char> Personaggi;
        std::list<p_obj> Oggetti;
        std::queue<char*>* globalnarrative;

    public:
        Mappa* next;
        Mappa* prev;
        //crea una nuova mappa popolata da stanza
        Mappa(int nRoomsPrec,int nLevel,queue<char*>* narrative);
//        Mappa(const Mappa& orig);
        //stampa la mappa con cout facendo solo 0 e 1
        void stampaMappa();
        //restituisce il carattere che sta alle coordinate specificate
        char getMapChar(int MapX,int MapY,int StX,int StY);
        //scrive sulla struttura dati di personaggio e lo sposta nella direzione specificata
        void moveChar(Character & personaggio,int dir);
        //mette il personaggio specificato(dovrebbe essere quello principale) sopra le scale che portano su come posizione iniziale
        void assegnaPosIniziale(Character* personaggio);
        //assegna la posizione specificata al personaggio passato per paramentro
        void assegnaPos(p_char personaggio,int MapX,int MapY,int StX,int StY);
        //Inserisce nella struttura dati l'oggetto passato
        void nuovoOggetto(Character oggetto);
        //ritorna vero se il personaggio inserito pu� muoversi nella direzione specificata , altimenti falso
        bool mapCanMove(Character & personaggio,int dir);
        //ritorna il valore di "esplorato" della stanza in quelle coordinate
        bool stanzaEsplorata(int MapX,int MapY);
        //fornisce una copia di "oggetti"
        std::list<p_char> getList();
        //Restituisce le due scale in modo da prenderne le posizioni
        pers getStairsUp();
        pers getStairsDown();


        Mappa* nextMap();
        Mappa* prevMap();

        void setPrev(Mappa* Map_Pointer);

        //riempie la stanza indicata di un numero casuale gi mostri e oggetti
        void populate(int MapX,int MapY);

        mapPos randStanzPos(int MapX,int MapY);
};


#endif //MAPPA_MAPPA_H
