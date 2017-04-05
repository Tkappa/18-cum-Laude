//
// Created by Igor Ershov on 05/04/2017.
//

#include "Stanza.h"
#include "Mappa.h"
#include <iostream>
#include <time.h>
#include <list>

//Decommentare per vedere i messaggi di debug della creazione della mappa
//#define debugmappa


struct posStanza{
    int x,y;
};

Mappa::Mappa(int n){
    //Inizializzo il random e vedo quante stanze in più avra questo livello
    srand(time(NULL));
    int stanzeAggiuntive= n +(rand()%2+1);
    //Questa variabile mi servirà dopo per vedere dove spunterà la stanza aggiuntiva
    int randCreazione;
    //Creo la struttura dati in cui verranno tenute le stanze esistenti
    std::list<posStanza> listStanze;

    //stabilisco la posizione della stanza iniziale
    int inizX=rand()%altezzaMappa;
    int inizY=rand()%lunghezzaMappa;
    mappa[inizX][inizY].creaStanza();

    //E lo aggiungo alla struttura dati
    posStanza a;
    a.x=inizX;
    a.y=inizY;
    listStanze.push_back(a);

    //Algoritmo di generazione stanze
    //Spiegazione: Ciclo finchè ci sono stanze da creare, Per ogni elemento della lista di stanze provo a crearci una stanza accanto
    // controllando sempre se non va fuori limiti o se esiste gia
    //se crea una nuova stanza la aggiunge alla lista e continua finchè non ci sono più stanze da creare
    // se nella creazione di una stanza "crea" una stanza già esistente , le unisce attraverso una porta
    while(stanzeAggiuntive>0) {
#ifdef debugmappa
        std::cout<<"stanze aggiuntive:"<<stanzeAggiuntive<<"\n";
#endif
        int x,y;
        for (std::list<posStanza>::iterator i = listStanze.begin(); i != listStanze.end()&&stanzeAggiuntive>0; ++i){
            randCreazione=rand()%6+1;
            x=(*i).x;
            y=(*i).y;
#ifdef debugmappa
            std::cout<<"Sto creando dalla stanza ("<<x<<","<<y<<") con randCreazione= "<<randCreazione<<"\n";
#endif
            switch (randCreazione) {
                //TODO:Controllare che la stanza esiste già,-> se esiste e non ha porta crea porta altrimenti nulla , ma non sottrarre stanzeAggiuntive
                //TODO:La cosa della lista quiindi olre a creare la stanza la aggiunge alla lista
                case 1:
                    //Sopra
                    if (x > 0) {
                        if (!mappa[x - 1][y].esiste()) {
                            mappa[x - 1][y].creaStanza();
                            mappa[x][y].creaPorta(1);
                            mappa[x - 1][y].creaPorta(3);
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
                            mappa[x][y].creaPorta(1);
                            mappa[x - 1][y].creaPorta(3);
                        }
                    }
                    break;
                case 2:
                    //Destra
                    if (y < lunghezzaMappa - 1) {
                        if (!mappa[x][y + 1].esiste()) {
                            mappa[x][y + 1].creaStanza();
                            mappa[x][y].creaPorta(2);
                            mappa[x][y + 1].creaPorta(0);
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
                            mappa[x][y].creaPorta(2);
                            mappa[x][y + 1].creaPorta(0);
                        }
                    }
                    break;
                case 3:
                    //Sotto
                    if (x < altezzaMappa - 1){
                        if(!mappa[x + 1][y].esiste()) {
                        mappa[x + 1][y].creaStanza();
                        mappa[x][y].creaPorta(3);
                        mappa[x + 1][y].creaPorta(1);
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
                            mappa[x][y].creaPorta(3);
                            mappa[x + 1][y].creaPorta(1);
                        }
                    }

                    break;
                case 4:
                    //Sinistra
                    if (y > 0) {
                        if (!mappa[x][y - 1].esiste()) {
                            mappa[x][y - 1].creaStanza();
                            mappa[x][y].creaPorta(0);
                            mappa[x][y - 1].creaPorta(2);
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
                            mappa[x][y].creaPorta(0);
                            mappa[x][y - 1].creaPorta(2);
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

}

void  Mappa::stampaMappa(){
    for (int i=0;i<altezzaMappa ;i++){
        for (int j=0;j<lunghezzaMappa;j++){
            if(!mappa[i][j].esiste()) std::cout<<0<<" ";
            else std::cout<<1<<" ";
            //mappa[i][j].stampaStanza();
        }
        std::cout<<"\n";
    }
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