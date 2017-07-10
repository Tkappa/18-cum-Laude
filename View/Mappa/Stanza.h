//
// Created by Igor Ershov on 29/03/2017.
//

#ifndef MAPPA_STANZA_H
#define MAPPA_STANZA_H

#include <string>
const int roomHeight=7,roomLenght=7;

class Room{
    protected:
    char room[roomLenght][roomHeight];
    bool explored;
    public:
    //Non fa assolutamente nulla
    Room();
    //Crea una stanza vuota
    void createRoom();
    //Stamperà a schermo il contenuto della stanza con i cout, metodo solo di debug
    void printRoom();
    //Creerà una porta nella direzione specificata direzione è il lato in cui verrà creata la porta, 1=sinista,2=su,3=destra,4=giu
    void createDoor(int Direction);
    //Mette il char carattere nella posizione specificata
    void createPos(int x,int y,std::string symbol);
    //restituisce il valore presente in x,y
    char getValue(int x,int y);
    //restituisce vero se la stanza è stata creata attraverso creaStanza()
    bool exists();
    //Restituisce vero o falso se da quella posizione ti puoi muovere nella direzione specificata
    bool canMove(int x,int y,int Direction);
    //cambia il falore di explored in true
    void exploration();
    //restituisce il valore di explored
    bool isExplored();
    //Restituisce vero se in quella direzione c'è una porta
    bool hasDoor(int Direction);
};


#endif //MAPPA_STANZA_H
