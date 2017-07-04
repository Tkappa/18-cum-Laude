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
string nome;
mapPos pos;
};
struct obj{
char nome;
mapPos pos;
};

typedef obj* p_obj;
typedef Character* p_char;
const int mapHeight=3,mapLenght=16;

class Map{
    protected:
        Room mapMatrix[mapHeight][mapLenght];
        int nLevel;
        pers stairsUp;
        pers stairDown;
        int nRooms;
        std::list<p_char> characterList;
        std::list<p_obj> objectList;
        std::queue<char*>* globalnarrative;

    public:
        //Puntatori alla mappa precedente e successiva
        Map* next;
        Map* prev;

        //crea una nuova mappa popolata da stanza
        Map(int nRoomsPrec,int nLevel,queue<char*>* narrative);
//        Mappa(const Mappa& orig);
        //stampa la mappa con cout facendo solo 0 e 1
        void printMap();
        //restituisce il carattere che sta alle coordinate specificate
        char getMapChar(int MapX,int MapY,int StX,int StY);
        //scrive sulla struttura dati di personaggio e lo sposta nella direzione specificata
        void moveChar(p_char personaggio,int dir);
        //mette il personaggio specificato(dovrebbe essere quello principale) sopra le scale che portano su come posizione iniziale
        void assignInizialPosition_toPlayer(p_char personaggio);
        //assegna la posizione specificata al personaggio passato per paramentro
        void assingPosition(p_char personaggio,int MapX,int MapY,int StX,int StY);
        //ritorna vero se il personaggio inserito pu� muoversi nella direzione specificata , altimenti falso
        bool mapCanMove(p_char personaggio,int dir);
        //ritorna il valore di "esplorato" della stanza in quelle coordinate
        bool roomExplored(int MapX,int MapY);
        //fornisce una copia di "oggetti"
        std::list<p_char> getList();
        //Restituisce le due scale in modo da prenderne le posizioni
        pers getStairsUp();
        pers getStairsDown();

        //Metodi che gestiscono il cambio di mappa
        Map* nextMap();
        Map* prevMap();

        //Metodo per inserire la mappa precedente alla mappa attuale
        void setPrev(Map* Map_Pointer);

        //riempie la stanza indicata di un numero casuale di mostri e oggetti
        void populate(int MapX,int MapY);
        //Metodo utile a populate per mettere una posizione casuale nella stanza all'oggetto creato
        mapPos randRoomPos(int MapX,int MapY);
};


#endif //MAPPA_MAPPA_H
