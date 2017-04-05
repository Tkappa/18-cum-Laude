//
// Created by Igor Ershov on 29/03/2017.
//

#ifndef MAPPA_STANZA_H
#define MAPPA_STANZA_H

const int altezzaStanza=11,lunghezzaStanza=11;
class Stanza{
    protected:
    char stanza[lunghezzaStanza][altezzaStanza];
    public:
    //Non fa assolutamente nulla
    Stanza();
    //Crea una stanza vuota
    void creaStanza();
    //Stamperà a schermo il contenuto della stanza
    void stampaStanza();
    //Creerà una porta nella direzione specificata direzione è il lato in cui verrà creata la porta, 0=sinista,1=su,2=destra,3=giu
    void creaPorta(int direzione);
    //Mette il char carattere nella posizione specificata TODO:Fare che elimini la posizione vecchia?
    void updatePos(int x,int y,char carattere);
};

#include "Stanza.cpp"
#endif //MAPPA_STANZA_H
