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
//#define debugMap
//#define debugMapVerbose



struct posStanza{
    int x,y;
};


Mappa::Mappa(int n,int nLevelPrec,queue<char*>* narrative){
#ifdef debugMap
    cout<<"Iniziato il costruttore Mappa()"<<endl;
#endif // debugMap
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
    mappa[inizX][inizY].createRoom();
    mappa[inizX][inizY].exploration();
    //creo le due scale e assegno la posizione della prima nella prima stanza ceata
    scalagiu.nome=">";
    scalasu.nome="<";
    scalasu.pos.mapX=inizX;
    scalasu.pos.mapY=inizY;
    scalasu.pos.stanzX=rand()%(roomLenght-2)+1;
    scalasu.pos.stanzY=rand()%(roomHeight-2)+1;

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
#ifdef debugMapVerbose
        std::cout<<"stanze aggiuntive:"<<stanzeAggiuntive<<"\n";
#endif

        for (std::list<posStanza>::iterator i = listStanze.begin(); i != listStanze.end()&&stanzeAggiuntive>0; ++i){
            randCreazione=rand()%8+1;
            x=(*i).x;
            y=(*i).y;
#ifdef debugMapVerbose
            std::cout<<"Sto creando dalla stanza ("<<x<<","<<y<<") con randCreazione= "<<randCreazione<<"\n";
#endif
            switch (randCreazione) {
                case 1:
                    //Sopra
                    if (x > 0) {
                        if (!mappa[x - 1][y].exists()) {
                            mappa[x - 1][y].createRoom();
                            mappa[x][y].createDoor(2);
                            mappa[x - 1][y].createDoor(4);
                            stanzeAggiuntive--;
                            posStanza b;
                            b.x = x - 1;
                            b.y = y;
                            listStanze.push_back(b);
#ifdef debugMapVerbose
                            std::cout<<"Stanza creata:";
                            std::cout<<b.x<<",";
                            std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].createDoor(2);
                            mappa[x - 1][y].createDoor(4);
                        }
                    }
                    break;
                case 2:
                case 6:
                    //Destra
                    if (y < lunghezzaMappa - 1) {
                        if (!mappa[x][y + 1].exists()) {
                            mappa[x][y + 1].createRoom();
                            mappa[x][y].createDoor(3);
                            mappa[x][y + 1].createDoor(1);
                            stanzeAggiuntive--;
                            posStanza b;
                            b.x = x;
                            b.y = y + 1;
                            listStanze.push_back(b);
#ifdef debugMapVerbose
                            std::cout<<"Stanza creata:";
                            std::cout<<b.x<<",";
                            std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].createDoor(3);
                            mappa[x][y + 1].createDoor(1);
                        }
                    }
                    break;
                case 3:
                    //Sotto
                    if (x < altezzaMappa - 1){
                        if(!mappa[x + 1][y].exists()) {
                        mappa[x + 1][y].createRoom();
                        mappa[x][y].createDoor(4);
                        mappa[x + 1][y].createDoor(2);
                        stanzeAggiuntive--;
                        posStanza b;
                        b.x=x + 1;
                        b.y=y;
                        listStanze.push_back(b);
#ifdef debugMapVerbose
                        std::cout<<"Stanza creata:";
                        std::cout<<b.x<<",";
                        std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].createDoor(4);
                            mappa[x + 1][y].createDoor(2);
                        }
                    }

                    break;
                case 4:
                case 7:
                    //Sinistra
                    if (y > 0) {
                        if (!mappa[x][y - 1].exists()) {
                            mappa[x][y - 1].createRoom();
                            mappa[x][y].createDoor(1);
                            mappa[x][y - 1].createDoor(3);
                            stanzeAggiuntive--;
                            posStanza b;
                            b.x = x;
                            b.y = y - 1;
                            listStanze.push_back(b);
#ifdef debugMapVerbose
                            std::cout<<"Stanza creata:";
                            std::cout<<b.x<<",";
                            std::cout<<b.y<<"\n";
#endif
                        }
                        else{
                            mappa[x][y].createDoor(1);
                            mappa[x][y - 1].createDoor(3);
                        }
                    }
                    break;
                default:
                    //Nessuna stanza
#ifdef debugMapVerbose
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
    scalagiu.pos.stanzX=rand()%(roomLenght-2)+1;
    scalagiu.pos.stanzY=rand()%(roomHeight-2)+1;

    //aggiungo entrambe le scale alla struttura dati
    mappa[scalagiu.pos.mapX][scalagiu.pos.mapY].createPos(scalagiu.pos.stanzX,scalagiu.pos.stanzY,scalagiu.nome);
    mappa[scalasu.pos.mapX][scalasu.pos.mapY].createPos(scalasu.pos.stanzX,scalasu.pos.stanzY,scalasu.nome);

#ifdef debugMap
    cout<<"Finito il costruttore Mappa()"<<endl;
#endif // debugMap
}

void  Mappa::stampaMappa(){
    for (int i=0;i<altezzaMappa ;i++){
        for (int j=0;j<lunghezzaMappa;j++){
            if(!mappa[i][j].exists()) std::cout<<0<<" ";
            else std::cout<<1<<" ";
        }
        std::cout<<"\n";
    }
}
char Mappa::getMapChar(int MapX,int MapY,int StX,int StY){
#ifdef debugMap
    cout<<"Entrato dentro getMapChar(), char e':";
    cout<<mappa[MapY][MapX].getValue(StX,StY)<<endl;
#endif // debugMap
    return mappa[MapY][MapX].getValue(StX,StY);
}
void Mappa::moveChar(Character & personaggio,int dir){
#ifdef debugMap
    cout<<"Inziato il metodo moveChar()"<<endl;
#endif // debugMap

    Pos p= personaggio.getPos();
    switch(dir){
        case 1:
            //sinistra
            if(p.stanzX==roomHeight/2 && p.stanzY==0){
                p.mapY=p.mapY-1;
                p.stanzY=roomHeight-1;
                if(!mappa[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzY=p.stanzY-1;
            break;
        case 2:
            //su
            if(p.stanzX==0 && p.stanzY==roomLenght/2){
                p.mapX=p.mapX-1;
                p.stanzX=roomLenght-1;

                if(!mappa[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzX=p.stanzX-1;
            break;
        case 3:
            //destra
            if(p.stanzX==roomLenght/2 && p.stanzY==roomHeight-1){
                p.mapY=p.mapY+1;
                p.stanzY=0;

                if(!mappa[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzY=p.stanzY+1;
            break;
        case 4:
            //giu
            if(p.stanzX==roomLenght-1 && p.stanzY==roomHeight/2){
                p.mapX=p.mapX+1;
                p.stanzX=0;

                if(!mappa[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mappa[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzX=p.stanzX+1;
            break;
    }
    personaggio.setPos(p);
#ifdef debugMap
    cout<<"Finito il metodo moveChar()"<<endl;
#endif // debugMap
}
void Mappa::assegnaPosIniziale(p_char personaggio){
#ifdef debugMap
    cout<<"Inziato il metodo assegnaPosIniziale()"<<endl;
#endif // debugMap
    //il personaggio iniziale spawnerà sempre sulle scale che portano al livello prima
    Pos p;
    p.mapX=scalasu.pos.mapX;
    p.mapY=scalasu.pos.mapY;
    p.stanzX=scalasu.pos.stanzX;
    p.stanzY=scalasu.pos.stanzY;

    personaggio->setPos(p);
    Personaggi.push_back(personaggio);
#ifdef debugMap
    cout<<"Finito il metodo assegnaPosIniziale()"<<endl;
#endif // debugMap
}
void Mappa::assegnaPos(p_char personaggio,int MapX,int MapY,int StX,int StY){
#ifdef debugMap
    cout<<"Inziato il metodo assegnaPos()"<<endl;
#endif // debugMap
    Pos p;
    p.mapX=MapX;
    p.mapY=MapY;
    p.stanzX=StX;
    p.stanzY=StY;
    personaggio->setPos(p);
    Personaggi.push_back(personaggio);
#ifdef debugMap
    cout<<"Finito il metodo moveChar()"<<endl;
#endif // debugMap
}
bool Mappa::mapCanMove(Character & personaggio,int dir){
#ifdef debugMap
    cout<<"Entrato dentro il metodo mapCanMove()"<<endl;
#endif // debugMap
    Pos p= personaggio.getPos();
    return mappa[p.mapX][p.mapY].canMove(p.stanzX,p.stanzY,dir);
}
bool Mappa::stanzaEsplorata(int MapX,int MapY){
#ifdef debugMap
    cout<<"Entrato dentro il metodo stanzaEsplorata()"<<endl;
#endif // debugMap
    return mappa[MapY][MapX].isExplored();
}

void Mappa::nuovoOggetto(Character oggetto){
#ifdef debugMap
    cout<<"Inziato il metodo nuovoOggetto()"<<endl;
#endif // debugMap
   mappa[oggetto.getPos().mapX][oggetto.getPos().mapY].createPos(oggetto.getPos().stanzX,oggetto.getPos().stanzY,oggetto.getSym());
#ifdef debugMap
    cout<<"Finito  il metodo nuovoOggetto()"<<endl;
#endif // debugMap
}
std::list<p_char> Mappa::getList(){
#ifdef debugMap
    cout<<"Entrato dentro il metodo getList()"<<endl;
#endif // debugMap
return Personaggi;
}

pers Mappa::getStairsUp(){
#ifdef debugMap
    cout<<"Entrato dentro il metodo getStairsUp()"<<endl;
#endif // debugMap
return  scalasu;
}
pers Mappa::getStairsDown(){
#ifdef debugMap
    cout<<"Inziato il metodo getStairsDown()"<<endl;
#endif // debugMap
return scalagiu;
}

 void Mappa::setPrev(Mappa* Map_Pointer){

   #ifdef debugMap
    cout<<"Entrato dentro il metodo setPreb()"<<endl;
#endif // debugMap
 prev=Map_Pointer;
 }
Mappa* Mappa::nextMap(){
#ifdef debugMap
    cout<<"Inziato il metodo nextMap()"<<endl;
#endif // debugMap
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
#ifdef debugMap
    cout<<"Finito il metodo nextMap()"<<endl;
#endif // debugMap
    return next;
}

Mappa* Mappa::prevMap(){
 #ifdef debugMap
    cout<<"Inziato il metodo prevMap()"<<endl;
#endif // debugMap
    if (!prev){
        //Schermata di uscita dal dungeon
    }
#ifdef debugMap
    cout<<"Finito il metodo prevMap()"<<endl;
#endif // debugMap
    return prev;
}

void Mappa::populate(int MapX,int MapY){
  #ifdef debugMap
    cout<<"Inziato il metodo populate()"<<endl;
#endif // debugMap
    int nNewMonsters=rand()%100+1;
    ability test;
    mapPos x=randStanzPos(MapX,MapY);
    p_char p= new MajorCharacter("test",test,x,"blabla",NULL);

    p->setSym("R");
    Personaggi.push_back(p);


    //ATTENZIONE SE CRASHA A CASO POTREBBE ESSERE QUESTO PEZZO DI CODICE
    char* str= new char[400];
    strcat(str,"Vedi '");
    strcat(str,p->getSym().c_str());
    strcat(str,"' , ");
    strcat(str,p->getName().c_str());

    globalnarrative->push(str);

#ifdef debugMapVerbose
    cout<<"Ho creato un nuovo personaggio:"<<p<<"\nQuesti sono tutti i personaggi:\n";

    for (list<p_char>::iterator i = Personaggi.begin(); i != Personaggi.end(); ++i)
        cout << *i <<", "<< (*i)->getSym()<< endl;
#endif // debugMapVerbose

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
#ifdef debugMap
    cout<<"Inziato il metodo populate()"<<endl;
#endif // debugMap
}

mapPos Mappa::randStanzPos(int MapX,int MapY){
  #ifdef debugMap
    cout<<"Inziato il metodo randStanzPos()"<<endl;
#endif // debugMap
    mapPos x;
    x.mapX=MapX;
    x.mapY=MapY;
    x.stanzX=1+(rand()%(roomLenght-2));
    x.stanzY=1+(rand()%(roomHeight-2));
#ifdef debugMap
    cout<<"Finito il metodo randStanzPos()"<<endl;
#endif // debugMap
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