//
// Created by Igor Ershov on 05/04/2017.
//




#include "Stanza.h"
#include "Mappa.h"
#include <iostream>
#include "../../model/pc/MajorCharacter.hpp"
#include <list>

#define SHOP 1
#define LAUREA 2

#include <string.h>

#include <cstdlib>

//Decommentare per vedere i messaggi di debug della creazione della mappa
//#define debugMap
//#define debugMapVerbose




struct posStanza{
    int x,y;
};

Map::Map(int n,int nLevelPrec,queue<char*>* narrative, int specialmap){
    isStore=false;
    globalnarrative=narrative;
    next = NULL;
    prev = NULL;

    nLevel=nLevelPrec+1;
    nRooms=n;

    int randBiome=rand()%4;
    switch (randBiome){
    case 0:
        biome=open_day;
        break;
    case 1:
        biome=piazza_verdi;
        break;
    case 2:
        biome=facolta;
        break;
    case 3:
        biome=sede_centrale;
        break;
        }

    int inizX=rand()%mapHeight;
    int inizY=rand()%mapLenght;
    mapMatrix[inizX][inizY].createRoom();
    mapMatrix[inizX][inizY].exploration();

    stairDown.nome=">";
    stairsUp.nome="<";
    stairsUp.pos.mapX=inizX;
    stairsUp.pos.mapY=inizY;
    stairsUp.pos.stanzX=1;
    stairsUp.pos.stanzY=3;
    mapMatrix[stairsUp.pos.mapX][stairsUp.pos.mapY].createPos(stairsUp.pos.stanzX,stairsUp.pos.stanzY,stairsUp.nome);

    if(specialmap==SHOP){
    isStore=true;
    stairDown.pos.mapX=inizX;
    stairDown.pos.mapY=inizY;
    stairDown.pos.stanzX=5;
    stairDown.pos.stanzY=3;
    mapMatrix[stairDown.pos.mapX][stairDown.pos.mapY].createPos(stairDown.pos.stanzX,stairDown.pos.stanzY,stairDown.nome);

    int nOggetti=rand()%7+1;
    for(int i=0;i<nOggetti;i++){
        int type=3;
        p_item ogg;
        while(type==3){
            ogg=new Item(nLevel+3,{0,0,0,0});
            type= ogg->getType();
        }

        store.addItem(ogg);

    }
    }
    else if(specialmap==LAUREA){
        p_item degree=new Item("Laurea",50,WEAPON);
        mapPos x;
        x.mapX=inizX;
        x.mapY=inizY;
        x.stanzX=5;
        x.stanzY=3;
        degree->setPos(x);
        degree->setSym("l");
        objectList.push_back(degree);
    }
}

Map::Map(int n,int nLevelPrec,queue<char*>* narrative,bioma biomaparametro){
#ifdef debugMap
    cout<<"Iniziato il costruttore Mappa()"<<endl;
#endif // debugMap

    //Inizializza i vari puntatori
    globalnarrative=narrative;
    next = NULL;
    prev = NULL;

    //assegno il bioma attuale;
    biome=biomaparametro;
    isStore=false;

    //Inizializzo il random e vedo quante stanze in più avra questo livello
    nLevel=nLevelPrec+1;


    int stanzeAggiuntive= n +(rand()%2+1);
    nRooms=stanzeAggiuntive;
    //Questa variabile mi servirà dopo per vedere dove spunterà la stanza aggiuntiva
    int randCreazione;
    //Creo la struttura dati in cui verranno tenute le stanze esistenti
    std::list<posStanza> listStanze;

    //stabilisco la posizione della stanza iniziale
    int inizX=rand()%mapHeight;
    int inizY=rand()%mapLenght;
    mapMatrix[inizX][inizY].createRoom();
    mapMatrix[inizX][inizY].exploration();
    //creo le due scale e assegno la posizione della prima nella prima stanza ceata
    stairDown.nome=">";
    stairsUp.nome="<";
    stairsUp.pos.mapX=inizX;
    stairsUp.pos.mapY=inizY;
    stairsUp.pos.stanzX=rand()%(roomLenght-2)+1;
    stairsUp.pos.stanzY=rand()%(roomHeight-2)+1;

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
                        if (!mapMatrix[x - 1][y].exists()) {
                            mapMatrix[x - 1][y].createRoom();
                            mapMatrix[x][y].createDoor(2);
                            mapMatrix[x - 1][y].createDoor(4);
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
                            mapMatrix[x][y].createDoor(2);
                            mapMatrix[x - 1][y].createDoor(4);
                        }
                    }
                    break;
                case 2:
                case 6:
                    //Destra
                    if (y < mapLenght - 1) {
                        if (!mapMatrix[x][y + 1].exists()) {
                            mapMatrix[x][y + 1].createRoom();
                            mapMatrix[x][y].createDoor(3);
                            mapMatrix[x][y + 1].createDoor(1);
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
                            mapMatrix[x][y].createDoor(3);
                            mapMatrix[x][y + 1].createDoor(1);
                        }
                    }
                    break;
                case 3:
                    //Sotto
                    if (x < mapHeight - 1){
                        if(!mapMatrix[x + 1][y].exists()) {
                        mapMatrix[x + 1][y].createRoom();
                        mapMatrix[x][y].createDoor(4);
                        mapMatrix[x + 1][y].createDoor(2);
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
                            mapMatrix[x][y].createDoor(4);
                            mapMatrix[x + 1][y].createDoor(2);
                        }
                    }

                    break;
                case 4:
                case 7:
                    //Sinistra
                    if (y > 0) {
                        if (!mapMatrix[x][y - 1].exists()) {
                            mapMatrix[x][y - 1].createRoom();
                            mapMatrix[x][y].createDoor(1);
                            mapMatrix[x][y - 1].createDoor(3);
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
                            mapMatrix[x][y].createDoor(1);
                            mapMatrix[x][y - 1].createDoor(3);
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
    stairDown.pos.mapX=(*i).x;
    stairDown.pos.mapY=(*i).y;
    stairDown.pos.stanzX=rand()%(roomLenght-2)+1;
    stairDown.pos.stanzY=rand()%(roomHeight-2)+1;

    //aggiungo entrambe le scale alla struttura dati
    mapMatrix[stairDown.pos.mapX][stairDown.pos.mapY].createPos(stairDown.pos.stanzX,stairDown.pos.stanzY,stairDown.nome);
    mapMatrix[stairsUp.pos.mapX][stairsUp.pos.mapY].createPos(stairsUp.pos.stanzX,stairsUp.pos.stanzY,stairsUp.nome);

#ifdef debugMap
    cout<<"Finito il costruttore Mappa()"<<endl;
#endif // debugMap
}

void  Map::printMap(){
    for (int i=0;i<mapHeight ;i++){
        for (int j=0;j<mapLenght;j++){
            if(!mapMatrix[i][j].exists()) std::cout<<0<<" ";
            else std::cout<<1<<" ";
        }
        std::cout<<"\n";
    }
}
char Map::getMapChar(int MapX,int MapY,int StX,int StY){
#ifdef debugMap
    cout<<"Entrato dentro getMapChar(), char e':";
    cout<<mapMatrix[MapY][MapX].getValue(StX,StY)<<endl;
#endif // debugMap
    return mapMatrix[MapY][MapX].getValue(StX,StY);
}
void Map::moveChar(p_char personaggio,int dir){
#ifdef debugMap
    cout<<"Inziato il metodo moveChar()"<<endl;
#endif // debugMap

    Pos p= personaggio->getPos();
    switch(dir){
        case 1:
            //sinistra
            if(p.stanzX==roomHeight/2 && p.stanzY==0){
                p.mapY=p.mapY-1;
                p.stanzY=roomHeight-1;
                if(!mapMatrix[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mapMatrix[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzY=p.stanzY-1;
            break;
        case 2:
            //su
            if(p.stanzX==0 && p.stanzY==roomLenght/2){
                p.mapX=p.mapX-1;
                p.stanzX=roomLenght-1;

                if(!mapMatrix[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mapMatrix[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzX=p.stanzX-1;
            break;
        case 3:
            //destra
            if(p.stanzX==roomLenght/2 && p.stanzY==roomHeight-1){
                p.mapY=p.mapY+1;
                p.stanzY=0;

                if(!mapMatrix[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mapMatrix[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzY=p.stanzY+1;
            break;
        case 4:
            //giu
            if(p.stanzX==roomLenght-1 && p.stanzY==roomHeight/2){
                p.mapX=p.mapX+1;
                p.stanzX=0;

                if(!mapMatrix[p.mapX][p.mapY].isExplored()){
                    populate(p.mapX,p.mapY);
                }
                mapMatrix[p.mapX][p.mapY].exploration();
            }
            else
                p.stanzX=p.stanzX+1;
            break;
    }
    personaggio->setPos(p);
#ifdef debugMap
    cout<<"Finito il metodo moveChar()"<<endl;
#endif // debugMap
}
void Map::assignInizialPosition_toPlayer(p_char personaggio){
#ifdef debugMap
    cout<<"Inziato il metodo assegnaPosIniziale()"<<endl;
#endif // debugMap
    //il personaggio iniziale spawnerà sempre sulle scale che portano al livello prima
    Pos p;
    p.mapX=stairsUp.pos.mapX;
    p.mapY=stairsUp.pos.mapY;
    p.stanzX=stairsUp.pos.stanzX;
    p.stanzY=stairsUp.pos.stanzY;

    personaggio->setPos(p);
    characterList.push_back(personaggio);
#ifdef debugMap
    cout<<"Finito il metodo assegnaPosIniziale()"<<endl;
#endif // debugMap
}
void Map::assingPosition(p_char personaggio,int MapX,int MapY,int StX,int StY){
#ifdef debugMap
    cout<<"Inziato il metodo assegnaPos()"<<endl;
#endif // debugMap
    Pos p;
    p.mapX=MapX;
    p.mapY=MapY;
    p.stanzX=StX;
    p.stanzY=StY;
    personaggio->setPos(p);
    characterList.push_back(personaggio);
#ifdef debugMap
    cout<<"Finito il metodo moveChar()"<<endl;
#endif // debugMap
}
bool Map::mapCanMove(p_char personaggio,int dir){
#ifdef debugMap
    cout<<"Entrato dentro il metodo mapCanMove()"<<endl;
#endif // debugMap
    Pos p= personaggio->getPos();
    return mapMatrix[p.mapX][p.mapY].canMove(p.stanzX,p.stanzY,dir);
}
bool Map::roomExplored(int MapX,int MapY){
#ifdef debugMap
    cout<<"Entrato dentro il metodo stanzaEsplorata()"<<endl;
#endif // debugMap
    return mapMatrix[MapY][MapX].isExplored();
}


std::list<p_char> Map::getListChar(){
#ifdef debugMap
    cout<<"Entrato dentro il metodo getList()"<<endl;
#endif // debugMap
return characterList;
}

pers Map::getStairsUp(){
#ifdef debugMap
    cout<<"Entrato dentro il metodo getStairsUp()"<<endl;
#endif // debugMap
return  stairsUp;
}
pers Map::getStairsDown(){
#ifdef debugMap
    cout<<"Inziato il metodo getStairsDown()"<<endl;
#endif // debugMap
return stairDown;
}

 void Map::setPrev(Map* Map_Pointer){

   #ifdef debugMap
    cout<<"Entrato dentro il metodo setPreb()"<<endl;
#endif // debugMap
        prev=Map_Pointer;
 }
Map* Map::nextMap(){
#ifdef debugMap
    cout<<"Inziato il metodo nextMap()"<<endl;
#endif // debugMap
    if (next==NULL){
        if(nLevel==15){
            Map * newmap= new Map(nRooms,nLevel,globalnarrative,LAUREA);
            next=newmap;
            newmap->setPrev(this);
        }
        else if(nLevel%4==0){
            Map * newmap= new Map(nRooms,nLevel,globalnarrative,SHOP);
            next=newmap;
            newmap->setPrev(this);
        }
        else{
            Map * newmap= new Map(nRooms,nLevel,globalnarrative,biome);
            next=newmap;
            newmap->setPrev(this);
        }

    }
#ifdef debugMap
    cout<<"Finito il metodo nextMap()"<<endl;
#endif // debugMap
    return next;
}

Map* Map::prevMap(){
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

std::list<p_item> Map::getListItem(){
return objectList;}
void Map::populate(int MapX,int MapY){
  #ifdef debugMap
    cout<<"Inziato il metodo populate()"<<endl;
#endif // debugMap
    int nNewMonsters=rand()%100+1;
    int nNewItems=rand()%100+1;
    char* str= new char[400];


    if(nNewMonsters<65){
        nNewMonsters=1;
    }
    else if(nNewMonsters<90){
        nNewMonsters=2;
    }
    else {
        nNewMonsters=3;
    }

    if(nNewItems<65){
        nNewItems=1;
    }
    else if(nNewItems<90){
        nNewItems=2;
    }
    else {
        nNewItems=3;
    }

    for(int i=0;i<nNewMonsters;i++){
    mapPos x=randRoomPos(MapX,MapY);
    p_char p= new MajorCharacter(biome,nLevel+1);
    p->setPos(x);
    characterList.push_back(p);
    strcpy(str,"Vedi '");
    strcat(str,p->getSym().c_str());
    strcat(str,"' , ");
    strcat(str,p->getName().c_str());

    globalnarrative->push(str);
}

    for(int i=0;i<nNewItems;i++){
    mapPos itemx=randRoomPos(MapX,MapY);
    p_item it=new Item(2,itemx);
    objectList.push_back(it);
}









#ifdef debugMapVerbose
    cout<<"Ho creato un nuovo personaggio:"<<p<<"\nQuesti sono tutti i personaggi:\n";

    for (list<p_char>::iterator i = characterList.begin(); i != characterList.end(); ++i)
        cout << *i <<", "<< (*i)->getSym()<< endl;
#endif // debugMapVerbose

#ifdef debugMap
    cout<<"Inziato il metodo populate()"<<endl;
#endif // debugMap
}

mapPos Map::randRoomPos(int MapX,int MapY){
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

void Map::addItem(p_item a){
    this->objectList.push_back(a);
}
bool Map::checkIfStore(){
return isStore;}


Room Map::getRoomForCoord(int posX, int posY) {

    return mapMatrix[posX][posY];
}

int Map::getNLevel(){
return nLevel;
}
