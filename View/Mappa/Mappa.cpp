//
// Created by Igor Ershov on 05/04/2017.
//

#include "Stanza.h"
#include "Mappa.h"
#include <iostream>
#include "../../model/pc/MajorCharacter.hpp"
#include <list>

#include <string.h>

#include <cstdlib>
//Decommentare per vedere i messaggi di debug della creazione della mappa
//#define debugmappa



struct posStanza{
    int x,y;
};

Mappa::Mappa(int n,int nLevelPrec,queue<char*>* narrative){

    globalnarrative=narrative;
    next = NULL;
    prev = NULL;
    //Inizializzo il random e vedo quante stanze in più avra questo livello
    nLevel=nLevelPrec+1;


    int stanzeAggiuntive= n +(rand()%2+1);
    nRooms=stanzeAggiuntive;
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

//Mappa::Mappa(const Mappa& orig){
//    mappa = orig.mappa;
//    scalasu = orig.scalasu;
//    scalagiu = orig.scalagiu;
//    Oggetti = orig.Oggetti;
//}

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
void Mappa::moveChar(Character & personaggio,int dir){
    Pos p= personaggio.getPos();
    switch(dir){
        case 1:
            //sinistra
            if(p.stanzX==altezzaStanza/2 && p.stanzY==0){
                p.mapY=p.mapY-1;
                p.stanzY=altezzaStanza-1;
                if(!mappa[p.mapX][p.mapY].isEsplorata()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].esplorazione();
            }
            else
                p.stanzY=p.stanzY-1;
            break;
        case 2:
            //su
            if(p.stanzX==0 && p.stanzY==lunghezzaStanza/2){
                p.mapX=p.mapX-1;
                p.stanzX=altezzaStanza-1;

                if(!mappa[p.mapX][p.mapY].isEsplorata()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].esplorazione();
            }
            else
                p.stanzX=p.stanzX-1;
            break;
        case 3:
            //destra
            if(p.stanzX==lunghezzaStanza/2 && p.stanzY==altezzaStanza-1){
                p.mapY=p.mapY+1;
                p.stanzY=0;

                if(!mappa[p.mapX][p.mapY].isEsplorata()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].esplorazione();
            }
            else
                p.stanzY=p.stanzY+1;
            break;
        case 4:
            //giu
            if(p.stanzX==lunghezzaStanza-1 && p.stanzY==altezzaStanza/2){
                p.mapX=p.mapX+1;
                p.stanzX=0;

                if(!mappa[p.mapX][p.mapY].isEsplorata()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].esplorazione();
            }
            else
                p.stanzX=p.stanzX+1;
            break;
    }
    personaggio.setPos(p);
}
void Mappa::assegnaPosIniziale(p_char personaggio){
    //il personaggio iniziale spawnerà sempre sulle scale che portano al livello prima
    Pos p;
    p.mapX=scalasu.pos.mapX;
    p.mapY=scalasu.pos.mapY;
    p.stanzX=scalasu.pos.stanzX;
    p.stanzY=scalasu.pos.stanzY;

    personaggio->setPos(p);
    Personaggi.push_back(personaggio);
}
void Mappa::assegnaPos(p_char personaggio,int MapX,int MapY,int StX,int StY){
    Pos p;
    p.mapX=MapX;
    p.mapY=MapY;
    p.stanzX=StX;
    p.stanzY=StY;
    personaggio->setPos(p);
    Personaggi.push_back(personaggio);
}
bool Mappa::mapCanMove(Character & personaggio,int dir){
    Pos p= personaggio.getPos();
    return mappa[p.mapX][p.mapY].canMove(p.stanzX,p.stanzY,dir);
}
bool Mappa::stanzaEsplorata(int MapX,int MapY){
    return mappa[MapY][MapX].isEsplorata();
}
void Mappa::nuovoOggetto(Character oggetto){
    mappa[oggetto.getPos().mapX][oggetto.getPos().mapY].creaPos(oggetto.getPos().stanzX,oggetto.getPos().stanzY,oggetto.getSym());
}
std::list<p_char> Mappa::getList(){
return Personaggi;
}

pers Mappa::getStairsUp(){
return  scalasu;
}
pers Mappa::getStairsDown(){
return scalagiu;
}

 void Mappa::setPrev(Mappa* Map_Pointer){
    prev=Map_Pointer;
 }
Mappa* Mappa::nextMap(){
if (next==NULL){
    Mappa * newmap= new Mappa(nRooms,nLevel,globalnarrative);

    std::cout<<"Ho creato la nuova mappa\n";
    newmap->stampaMappa();

    std::cout<<"Ho assegnato la nuova mappa al puntatore\n";
    //newmap.setPrev(Map_P);

    std::cout<<"Ho messo il puntatore dentro il next della mappa corrente\n";
    next=newmap;
    newmap->setPrev(this);
    next->stampaMappa();
}

    std::cout<<"Ho fatto il return di next\n";
    return next;
}

Mappa* Mappa::prevMap(){
    if (!prev){
        //Schermata di uscita dal dungeon
    }
    return prev;
}

void Mappa::populate(int MapX,int MapY){
    int nNewMonsters=rand()%100+1;
    ability test;
    mapPos x=randStanzPos(MapX,MapY);
    p_char p= new MajorCharacter("test",test,x,"blabla",NULL);

    p->setSym('R');
    Personaggi.push_back(p);


    char* strin= "Vedi '";
    size_t len = strlen(strin);
    char* str = new char[len+2];
    strcpy(str,strin);
    str[len] = p->getSym();
    str[len+1] = '\0';
    strcat(str,"' , ");
    strcat(str,p->getName().c_str());
    globalnarrative->push(str);

    cout<<"Ho creato un nuovo personaggio:"<<p<<"\nQuesti sono tutti i personaggi:\n";

    for (list<p_char>::iterator i = Personaggi.begin(); i != Personaggi.end(); ++i)
        cout << *i <<", "<< (*i)->getSym()<< endl;
    //if(nNewMonsters<=50){
        //MajorCharacter a= randNPC();
        //Personaggi.push_back(a);


    //}
    /*else if(nNewMonsters>50 && nNewMonsters<=85){
        //MajorCharacter a
        mapPos x=randStanzPos(MapX,MapY);
    MajorCharacter a("test",test,x,"blabla",NULL);
     a.setSym('R');
        for(int i=0;i<2;i++){
            //a= randNPC();
            //Personaggi.push_back(a);
            x= randStanzPos(MapX,MapY);
            a.setPos(x);
        Personaggi.push_back(a);

        Personaggi.push_back(a);
        }
    }*/
    /*else if(nNewMonsters>85){
        //MajorCharacter a
        for(int i=0;i<3;i++){
            //a= randNPC();
            //Personaggi.push_back(a);
            x= randStanzPos(MapX,MapY);
        a=new MajorCharacter("pippo",{0,0,0,0},x);
        a.setSym('R');
        Personaggi.push_back(a);
        }
    }*/
    /*int nNewObjects=rand()%100+1;
    if(nNewObjects<=50){
        //MajorCharacter a= randNPC();
        //Personaggi.push_back(a);

    }
    else if(nNewObjects>50 && nNewObjects<=85){
        //MajorCharacter a
        for(int i=0;i<2;i++){
            //a= randNPC(nLevel);
            //Personaggi.push_back(a);
        }
    }
    else if(nNewObjects>85){
        //MajorCharacter a
        for(int i=0;i<3;i++){
            //a= randNPC();
            //Personaggi.push_back(a);
        }
    }*/

}

mapPos Mappa::randStanzPos(int MapX,int MapY){
    mapPos x;
    x.mapX=MapX;
    x.mapY=MapY;
    x.stanzX=1+(rand()%(altezzaStanza-2));
    x.stanzY=1+(rand()%(lunghezzaStanza-2));
    return x;
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
