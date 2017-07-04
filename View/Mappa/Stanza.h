//
// Created by Igor Ershov on 29/03/2017.
//

#ifndef MAPPA_STANZA_H
#define MAPPA_STANZA_H

const int altezzaStanza=7,lunghezzaStanza=7;
class Stanza{
    protected:
    char stanza[lunghezzaStanza][altezzaStanza];
    bool esplorata;
    public:
    //Non fa assolutamente nulla
    Stanza();
    //Crea una stanza vuota
    void creaStanza();
    //Stamperà a schermo il contenuto della stanza
    void stampaStanza();
    //Creerà una porta nella direzione specificata direzione è il lato in cui verrà creata la porta, 1=sinista,2=su,3=destra,4=giu
    void creaPorta(int direzione);
    //Mette il char carattere nella posizione specificata
    void creaPos(int x,int y,char carattere);
    //restituisce il valore presente in x,y
    char getValue(int x,int y);
    //restituisce vero se la stanza è stata creata attraverso creaStanza()
    bool esiste();
    //Restituisce vero o falso se da quella posizione ti puoi muovere nella direzione specificata
    bool canMove(int x,int y,int dir);
    //cambia il falore di esplorata in true e la popola di mostri/oggetti
    void esplorazione();
    //restituisce il valore di esplorata
    bool isEsplorata();
};


#endif //MAPPA_STANZA_H
