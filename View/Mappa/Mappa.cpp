//
// Created by Igor Ershov on 05/04/2017.
//

#include "Stanza.h"
#include "Mappa.h"
#include <iostream>
#include <list>

#include <cstdlib>
//Decommentare per vedere i messaggi di debug della creazione della mappa
//#define debugmappa



struct posStanza{
    int x,y;
};

Mappa::Mappa(int n){



    //Inizializzo il random e vedo quante stanze in più avra questo livello


    int stanzeAggiuntive= n +(rand()%2+1);
    //Questa variabile mi servirà dopo per vedere dove spunterà la stanza aggiuntiva
    int randCreazione;
    //Creo la struttura dati in cui verranno tenute le stanze esistenti
    std::list<posStanza> listStanze;

    //stabilisco la posizione della stanza iniziale
    int inizX=rand()%altezzaMappa;
    int inizY=rand()%lunghezzaMappa;
    mappa[inizX][inizY].creaStanza();
    mappa[inizX][inizY].esplorazione();
    //creo le due scale e assegno la posizione della prima nella prima stanza ceata
    scalagiu.nome='>';
    scalasu.nome='<';
    scalasu.pos.mapX=inizX;
    scalasu.pos.mapY=inizY;
    scalasu.pos.stanzX=rand()%(lunghezzaStanza-2)+1;
    scalasu.pos.stanzY=rand()%(altezzaStanza-2)+1;

    //E lo aggiungo alla struttura dati
    posStanza a;
    a.x=inizX;
    a.y=inizY;
    listStanze.push_back(a);

    int x,y;
    //Algoritmo di generazione stanze
    //Spiegazione: Ciclo finchè ci sono stanze da creare, Per ogni elemento della lista di stanze provo a crearci una stanza accanto
    // controllando sempre se non va fuori limiti o se esiste gia
    //se crea una nuova stanza la aggiunge alla lista e continua finchè non ci sono più stanze da creare
    // se nella creazione di una stanza "crea" una stanza già esistente , le unisce attraverso una porta
    while(stanzeAggiuntive>0) {
#ifdef debugmappa
        std::cout<<"stanze aggiuntive:"<<stanzeAggiuntive<<"\n";
#endif

        for (std::list<posStanza>::iterator i = listStanze.begin(); i != listStanze.end()&&stanzeAggiuntive>0; ++i){
            randCreazione=rand()%8+1;
            x=(*i).x;
            y=(*i).y;
#ifdef debugmappa
            std::cout<<"Sto creando dalla stanza ("<<x<<","<<y<<") con randCreazione= "<<randCreazione<<"\n";
#endif
            switch (randCreazione) {
                case 1:
                    //Sopra
                    if (x > 0) {
                        if (!mappa[x - 1][y].esiste()) {
                            mappa[x - 1][y].creaStanza();
                            mappa[x][y].creaPorta(2);
                            mappa[x - 1][y].creaPorta(4);
                            stanzeAggiuntive--;
                            posStanza b;
                            b.x = x - 1;
                            b.y = y;
                            listStanze.push_back(b);
#ifdef debugmappa
                            std::cout<<"Stanza creata:";
                            std::cout<<b.x<<",";
                            std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].creaPorta(2);
                            mappa[x - 1][y].creaPorta(4);
                        }
                    }
                    break;
                case 2:
                case 6:
                    //Destra
                    if (y < lunghezzaMappa - 1) {
                        if (!mappa[x][y + 1].esiste()) {
                            mappa[x][y + 1].creaStanza();
                            mappa[x][y].creaPorta(3);
                            mappa[x][y + 1].creaPorta(1);
                            stanzeAggiuntive--;
                            posStanza b;
                            b.x = x;
                            b.y = y + 1;
                            listStanze.push_back(b);
#ifdef debugmappa
                            std::cout<<"Stanza creata:";
                            std::cout<<b.x<<",";
                            std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].creaPorta(3);
                            mappa[x][y + 1].creaPorta(1);
                        }
                    }
                    break;
                case 3:
                    //Sotto
                    if (x < altezzaMappa - 1){
                        if(!mappa[x + 1][y].esiste()) {
                        mappa[x + 1][y].creaStanza();
                        mappa[x][y].creaPorta(4);
                        mappa[x + 1][y].creaPorta(2);
                        stanzeAggiuntive--;
                        posStanza b;
                        b.x=x + 1;
                        b.y=y;
                        listStanze.push_back(b);
#ifdef debugmappa
                        std::cout<<"Stanza creata:";
                        std::cout<<b.x<<",";
                        std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].creaPorta(4);
                            mappa[x + 1][y].creaPorta(2);
                        }
                    }

                    break;
                case 4:
                case 7:
                    //Sinistra
                    if (y > 0) {
                        if (!mappa[x][y - 1].esiste()) {
                            mappa[x][y - 1].creaStanza();
                            mappa[x][y].creaPorta(1);
                            mappa[x][y - 1].creaPorta(3);
                            stanzeAggiuntive--;
                            posStanza b;
                            b.x = x;
                            b.y = y - 1;
                            listStanze.push_back(b);
#ifdef debugmappa
                            std::cout<<"Stanza creata:";
                            std::cout<<b.x<<",";
                            std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].creaPorta(1);
                            mappa[x][y - 1].creaPorta(3);
                        }
                    }
                    break;
                default:
                    //Nessuna stanza
#ifdef debugmappa
                    std::cout<<"Nessuna stanza creata da base:";
                    std::cout<<x<<",";
                    std::cout<<y<<"\n";
#endif
                    break;
            }
        }
    }

    //assegno al posizione ella seconda scala creata
    std::list<posStanza>::iterator i= listStanze.end();
    i--;
    scalagiu.pos.mapX=(*i).x;
    scalagiu.pos.mapY=(*i).y;
    scalagiu.pos.stanzX=rand()%(altezzaStanza-2)+1;
    scalagiu.pos.stanzY=rand()%(altezzaStanza-2)+1;

    //aggiungo entrambe le scale alla struttura dati
    mappa[scalagiu.pos.mapX][scalagiu.pos.mapY].creaPos(scalagiu.pos.stanzX,scalagiu.pos.stanzY,scalagiu.nome);
    mappa[scalasu.pos.mapX][scalasu.pos.mapY].creaPos(scalasu.pos.stanzX,scalasu.pos.stanzY,scalasu.nome);

}

void  Mappa::stampaMappa(){
    for (int i=0;i<altezzaMappa ;i++){
        for (int j=0;j<lunghezzaMappa;j++){
            if(!mappa[i][j].esiste()) std::cout<<0<<" ";
            else std::cout<<1<<" ";
        }
        std::cout<<"\n";
    }
}
char Mappa::getMapChar(int MapX,int MapY,int StX,int StY){
    return mappa[MapY][MapX].getValue(StX,StY);
}
void Mappa::moveChar(pers * personaggio,int dir){
    switch(dir){
        case 1:
            //sinistra
            if(personaggio->pos.stanzX==altezzaStanza/2 && personaggio->pos.stanzY==0){
                personaggio->pos.mapY=personaggio->pos.mapY-1;
                personaggio->pos.stanzY=altezzaStanza-1;
                mappa[personaggio->pos.mapX][personaggio->pos.mapY].esplorazione();
            }
            else
                personaggio->pos.stanzY=personaggio->pos.stanzY-1;
            break;
        case 2:
            //su
            if(personaggio->pos.stanzX==0 && personaggio->pos.stanzY==lunghezzaStanza/2){
                personaggio->pos.mapX=personaggio->pos.mapX-1;
                personaggio->pos.stanzX=altezzaStanza-1;
                mappa[personaggio->pos.mapX][personaggio->pos.mapY].esplorazione();
            }
            else
                personaggio->pos.stanzX=personaggio->pos.stanzX-1;
            break;
        case 3:
            //destra
            if(personaggio->pos.stanzX==lunghezzaStanza/2 && personaggio->pos.stanzY==altezzaStanza-1){
                personaggio->pos.mapY=personaggio->pos.mapY+1;
                personaggio->pos.stanzY=0;
                mappa[personaggio->pos.mapX][personaggio->pos.mapY].esplorazione();
            }
            else
                personaggio->pos.stanzY=personaggio->pos.stanzY+1;
            break;
        case 4:
            //giu
            if(personaggio->pos.stanzX==lunghezzaStanza-1 && personaggio->pos.stanzY==altezzaStanza/2){
                personaggio->pos.mapX=personaggio->pos.mapX+1;
                personaggio->pos.stanzX=0;
                mappa[personaggio->pos.mapX][personaggio->pos.mapY].esplorazione();
            }
            else
                personaggio->pos.stanzX=personaggio->pos.stanzX+1;
            break;
    }
}
void Mappa::assegnaPosIniziale(pers *personaggio){
    //il personaggio iniziale spawnerà sempre sulle scale che portano al livello prima
    personaggio->pos.mapX=scalasu.pos.mapX;
    personaggio->pos.mapY=scalasu.pos.mapY;
    personaggio->pos.stanzX=scalasu.pos.stanzX;
    personaggio->pos.stanzY=scalasu.pos.stanzY;
    Oggetti.push_back(personaggio);
}
void Mappa::assegnaPos(pers *personaggio,int MapX,int MapY,int StX,int StY){
    personaggio->pos.mapX=MapX;
    personaggio->pos.mapY=MapY;
    personaggio->pos.stanzX=StX;
    personaggio->pos.stanzY=StY;
    Oggetti.push_back(personaggio);
}
bool Mappa::mapCanMove(pers * personaggio,int dir){
    return mappa[personaggio->pos.mapX][personaggio->pos.mapY].canMove(personaggio->pos.stanzX,personaggio->pos.stanzY,dir);
}
bool Mappa::stanzaEsplorata(int MapX,int MapY){
    return mappa[MapY][MapX].isEsplorata();
}
void Mappa::nuovoOggetto(pers oggetto){
    mappa[oggetto.pos.mapX][oggetto.pos.mapY].creaPos(oggetto.pos.stanzX,oggetto.pos.stanzY,oggetto.nome);
}
std::list<p_pers> Mappa::getList(){
return Oggetti;
}






//TURORIAL LISTE c++
/*
    std::list<posStanza> listStanze; crei la lista
    posStanza a; crei un elemento
    a.x=2;
    a.y=4;
    listStanze.push_back(a); lo metti alla fine
    for (list<posStanza>::iterator i = listStanze.begin(); i != listStanze.end(); ++i) stampi tutti i valori
        std::cout << (*i).x << endl;
 */
