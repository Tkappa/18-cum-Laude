//
// Created by Igor Ershov on 05/04/2017.
//

#ifndef MAPPA_MAPPA_H
#define MAPPA_MAPPA_H
#include <list>
#include "Stanza.h"

struct posizione{
int mapX,mapY,stanzX,stanzY;
};
struct pers{
char nome;
posizione pos;
};
typedef pers* p_pers;
const int altezzaMappa=3,lunghezzaMappa=16;
class Mappa{
    protected:
        Stanza mappa[altezzaMappa][lunghezzaMappa];
        pers scalasu;
        pers scalagiu;
        std::list<p_pers> Oggetti;
    public:
        //crea una nuova mappa popolata da stanza
        Mappa(int nLivelliPrec);
        //stampa la mappa con cout facendo solo 0 e 1
        void stampaMappa();
        //restituisce il carattere che sta alle coordinate specificate
        char getMapChar(int MapX,int MapY,int StX,int StY);
        //scrive sulla struttura dati di personaggio e lo sposta nella direzione specificata
        void moveChar(pers * personaggio,int dir);
        //mette il personaggio specificato(dovrebbe essere quello principale) sopra le scale che portano su come posizione iniziale
        void assegnaPosIniziale(pers *personaggio);
        //assegna la posizione specificata al personaggio passato per paramentro
        void assegnaPos(pers *personaggio,int MapX,int MapY,int StX,int StY);
        //Inserisce nella struttura dati l'oggetto passato
        void nuovoOggetto(pers oggetto);
        //ritorna vero se il personaggio inserito può muoversi nella direzione specificata , altimenti falso
        bool mapCanMove(pers * personaggio,int dir);
        //ritorna il valore di "esplorato" della stanza in quelle coordinate
        bool stanzaEsplorata(int MapX,int MapY);
        //fornisce una copia di "oggetti"
        std::list<p_pers> getList();

};


#endif //MAPPA_MAPPA_H
