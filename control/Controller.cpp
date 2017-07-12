#ifdef __APPLE__ && __MACH__
    #include <ncurses.h>
#else
    #include <ncurses/curses.h>
#endif

#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "../model/pc/Item.hpp"
#include "../model/pc/Character.hpp"
#include "../model/pc/MajorCharacter.hpp"
#include "../model/npc/Follower.hpp"
#include "../view/mappa/Mappa.h"
#include "../view/View.h"
#include "Controller.h"
#include <string.h>
#include <stdio.h>

#define SEE 1
#define DROP 2
#define EQUIP 3
#define BUY 4


using namespace std;

Controller::Controller(int nLevels) {
//    vista;
    //    Mappa tmpMap(nLevels);
    //    map = tmpMap;
}


void Controller::launch() {
    //crea il random
    time_t t;
    srand((unsigned) time(&t));

    //crea la struttura dati con 3 stanze base
    Map* head;
    head= new Map(1,1,&narrative,open_day);
    Map* curMap=head;

    //setup di ncurses , queste ci vogliono sempre
    initscr(); //inizializza ncurses
    clear(); //pulisce la console
    cbreak(); // toglie la necessita di premere invio ad ogni comando
    curs_set(0); //toglie il cursore
    keypad(stdscr, TRUE); //offre la possibilit� di usare tasti speciali (freccette etc..)

    //inizializzazione della classe view
    View vista;

    //creazione del personaggio
    MajorCharacter pg=pgInitialization(vista);
    p_char punt_pg=&pg;
    curMap->assignInizialPosition_toPlayer(punt_pg);

    noecho(); //toglie gli input a schermo

    //stampa l'interfaccia utente
    vista.print_nameAndStats(punt_pg);

    vista.print_outputMap(curMap);
    char iniz[500]="Questa sara' una grande avventura!";
    narrative.push(iniz);
    vista.print_narrative(&narrative);

    refresh();



    //Questo � un abbozzo di movimento
    int c;
    int mov;
    bool turno= true;

    vista.print_help();
    c=getch();
    vista.print_outputMap(curMap);

    while (1) {
        for (auto character : curMap->characterList) {
            if (character->getSym() != pg.getSym()) {
                int direction = character->moveToChar(&pg, curMap->getRoomForCoord(character->pos.mapX, character->pos.mapY));

                if (curMap->mapCanMove(character, direction))
                    curMap->moveChar(character, direction);
            }
        }

        c = getch();

        switch (c) { //se il tasto premuto � "s" oppure freccia sinistra
            case 97:// char 'a'
            case 260:// left
                //controlla se si puo muovere in quella posizione
                if (curMap->mapCanMove(punt_pg, 1))
                    // e in tal caso muovilo verso la posizione
                    curMap->moveChar(punt_pg, 1);
                vista.print_outputMap(curMap);
                break;
            case 100:// char 'd'
            case 261:// right
                if (curMap->mapCanMove(punt_pg, 3))
                    curMap->moveChar(punt_pg, 3);
                vista.print_outputMap(curMap);
                break;
            case 119:// char 'w'
            case 259:// su
                if (curMap->mapCanMove(punt_pg, 2))
                    curMap->moveChar(punt_pg, 2);
                vista.print_outputMap(curMap);
                break;
            case 115:// char 's'
            case 258:// giu
                if (curMap->mapCanMove(punt_pg, 4))
                    curMap->moveChar(punt_pg, 4);
                vista.print_outputMap(curMap);
                break;
            case 62:{//char >
                pers stairs=curMap->getStairsDown();
                if (stairs.pos.mapX==pg.getPos().mapX&&stairs.pos.mapY==pg.getPos().mapY && stairs.pos.stanzX==pg.getPos().stanzX && stairs.pos.stanzY==pg.getPos().stanzY){
                    curMap=curMap->nextMap();
                    curMap->assignInizialPosition_toPlayer(punt_pg);
                }}
                vista.clearoutputMap();
                vista.print_outputMap(curMap);
                break;
            case 60://char <
                {pers stairs=curMap->getStairsUp();
                if (stairs.pos.mapX==pg.getPos().mapX&&stairs.pos.mapY==pg.getPos().mapY && stairs.pos.stanzX==pg.getPos().stanzX && stairs.pos.stanzY==pg.getPos().stanzY){
                    curMap=curMap->prevMap();
                    stairs=curMap->getStairsDown();
                    mapPos x=stairs.pos;
                    curMap->assingPosition(punt_pg,x.mapX,x.mapY,x.stanzX,x.stanzY);
                }
                vista.clearoutputMap();
                vista.print_outputMap(curMap);
                }
                break;
            case 105://char i ( visualizza l'inventario
                vista.print_inventory(pg.getInventory(),SEE);
                turno = false;
                break;
            case 116://char t ( schermata di acquisto)
                if(curMap->checkIfStore()){
                    vista.print_inventory(curMap->store,BUY);
                    bool finished=false;
                    char* msg= new char[500];
                    strcpy(msg,"Lettera selezionata invalida");
                    while(!finished){
                        c=getch();
                        if (c=='k'){finished=true;}
                        int status=buy(punt_pg,c,curMap);
                        if(status==3){
                            finished=true;

                        }
                        else if(status==2){
                            strcpy(msg,"Non hai abbastanza spazio nell'inventario");
                        }
                        else if(status==1){
                            strcpy(msg,"Non hai abbastanza CFU per aquistare l'oggetto");
                        }
                        narrative.push(msg);
                        vista.print_narrative(&narrative);
                    }}

                vista.print_outputMap(curMap);
                break;
            case 103://char g //Selezione dell'oggetto da buttare a terra
                {vista.print_inventory(pg.getInventory(),DROP);
                bool finished=false;
                while(!finished){
                    c=getch();
                    if (c=='k'){finished=true;}
                    if(drop(punt_pg,c,curMap)){
                        finished=true;
                    }
                }
                }
                break;
            case 101://char e  selezione dell'oggetto da equipaggiare
                {vista.print_inventory(pg.getInventory(),EQUIP);
                bool finished=false;
                while(!finished){
                    c=getch();
                    if (c=='k'){finished=true;}
                    if(equip(punt_pg,c)){
                        finished=true;
                    }
                }
                if(punt_pg->getCurWeapon()->getName()=="Laurea"){
                    vista.print_victory();
                    c=getch();
                    exit(1);
                }
                }break;
            case 108://char l raccoglie l'oggetto da terra
                loot(punt_pg,curMap);
                break;
            case 109://char m  suicidio
                vista.print_death(punt_pg);
                c=getch();
                exit(1);
                break;
            case 110://char n vittoria
                vista.print_victory();
                c=getch();
                exit(1);
                break;
        }

        if (c == 113)// char 'q'  per uscire
        {
            vista.print_exitconfirmation();
            c=getch();
            if(c=='y'||c=='Y'){
                break;
            }
            vista.print_outputMap(curMap);

        }


    if(turno){
        vista.print_narrative(&narrative);
        vista.print_nameAndStats(punt_pg);
    }
    turno=true;
    }

    refresh();
}

void Controller::testFollower() {
    Follower gino;
    cout << gino.toStr();
}

void Controller::loot(p_char pg, Map* curMap){
    mapPos pgpos;
    pgpos=pg->getPos();
    std::list<p_item> items=curMap->objectList;
    for (std::list<p_item>::iterator i = items.begin(); i != items.end();/*si incementa durante il ciclo*/){
        if(pgpos.mapX==(*i)->position.mapX && pgpos.mapY==(*i)->position.mapY &&  pgpos.stanzX==(*i)->position.stanzX &&  pgpos.stanzY==(*i)->position.stanzY){
            //crea un nuovo iteratore e lo mette allo step successivo cosi può cancellare tranquillamente
            std::list<p_item>::iterator new_i = i;
            ++new_i;
            //mette il puntatore corrente in una variabile temporanea
            p_item temp=*i;
            //cancella il puntatore corrente dalla lista degli oggetti della mappa
            if(temp->getType()==3){

                items.remove((*i));
                pg->addMoney(temp->getValue());
                char* str= new char[400];
                strcpy(str,"Raccogli '");
                char buf[10];
                sprintf(buf,"%d",temp->getValue());
                strcat(str,buf);
                strcat(str,"' CFU da terra!");
                narrative.push(str);
            }
            else{
                    if(pg->pg_inventory.addItem(temp)){

                        items.remove((*i));
                        char* str= new char[400];
                        strcpy(str,"Raccogli '");
                        strcat(str,temp->getName().c_str());
                        strcat(str,"' da terra , e' un");
                        switch(temp->getType()){
                            case 1:
                                strcat(str,"'arma!");
                                break;
                            case 2:
                                strcat(str,"'armatura!");
                                break;
                            case 4:
                                strcat(str,"a pozione!");
                                break;
                        }

                        narrative.push(str);
                    }
                    else{
                        ++i;
                        char* bla=new char[500];
                        strcpy(bla,"Hai l'inventario pieno e non puoi raccogliere niente");
                        narrative.push(bla);
                    }
            }
            //mette l'iteratore alla posizione corretta dopo l'eliminazione
            i=new_i;
        }
        else{
            ++i;
        }
    }
    curMap->objectList=items;
}

bool Controller::drop(p_char pg,char c,Map* curMap){
    string tempchar="a";
    tempchar[0]=c;
    std::list<p_item> pg_inventorytemp=pg->pg_inventory.getInventory();
    p_item tempp=pg->pg_inventory.deleteItem(tempchar);
    if(tempp!=nullptr){
        tempp->position=pg->getPos();
        curMap->addItem(tempp);
        return true;
    }
    return false;
    }

bool Controller::equip(p_char pg, char c){
    string tempchar="a";
    tempchar[0]=c;
    char* msg= new char[500];
    bool usedpotion=false;
    std::list<p_item> pg_inventorytemp=pg->pg_inventory.getInventory();
    for (std::list<p_item>::iterator i = pg_inventorytemp.begin(); i != pg_inventorytemp.end();++i){
        if(tempchar==(*i)->getInventoryId()&&((*i)->getType()!=3)){
            p_item temp=(*i);
            p_item add;
            switch((*i)->getType()){
                case 1:{
                    add=pg->equipWeapon(temp);
                    strcpy(msg,"Hai equipaggiato ");
                    strcat(msg,temp->getName().c_str());
                    strcat(msg, " come arma!");
                }
                    break;
                case 2:{
                    add=pg->equipArmor(temp);
                    strcpy(msg,"Hai equipaggiato ");
                    strcat(msg,temp->getName().c_str());
                    strcat(msg, " come armatura!");
                }
                    break;

                case 4:
                    int curlife=pg->getFullStats().getLife();
                    int maxlife=pg->getBaseStats().getLife();
                    int value=(*i)->getValue();
                    ability temp=pg->getFullStats();
                    curlife+=value;
                    int dif=value;
                    if (curlife>maxlife){
                        dif=(curlife-dif)-maxlife;
                        curlife=maxlife;
                    }
                    temp.setLife(curlife);
                    pg->setFullStats(temp);
                    usedpotion=true;
                    strcpy(msg,"Hai usato una ");
                    strcat(msg,(*i)->getName().c_str());
                    strcat(msg, " e hai guadagnato ");
                    char buffer[3];
                    sprintf(buffer,"%d",dif);
                    strcat(msg,buffer);
                    strcat(msg," punti vita!" );
                    break;
            }
            //Qua si assume che si è ancora nella classe controller e quindi si ha un accesso a narrative, passateglielo come paramentro se no
            narrative.push(msg);
            pg->pg_inventory.deleteItem(tempchar);
            if(!usedpotion){ pg->pg_inventory.addItem(add);}
            return true;
        }
    }
    return false;
}

int Controller::buy(p_char pg,char c,Map* curMap){
    string tempchar="a";
    tempchar[0]=c;
    p_item selectedItem=curMap->store.getByID(tempchar);
    if(selectedItem!=nullptr){

        int moneyafterbought=(pg->getMoney())-(selectedItem->getPrice());
        if(moneyafterbought>=0){
            if(pg->pg_inventory.getSize()<8){
                pg->pg_inventory.addItem(curMap->store.deleteItem(tempchar));
                pg->setMoney(moneyafterbought);
                //successo
                return 3;
            }
            //inventario pieno
            return 2;
        }
        //non abbastanza soldi
        return 1;
    }
    //Non c'è l'oggetto
    return 0;
}

void Controller::testAttack() {
    ability s;
    //    cout<<s.to_str();
    //    Pos p = {0, 0, 0, 0};
    //    MajorCharacter mario("Mario", s, p, "Qualcosa", NULL);
    //    cout << mario.toStr();
    //    MajorCharacter anto("Antonio", s, p, "Qualcos'altro", NULL);
    //    cout << anto.toStr();
    //    cout << "Mario attack Anto\n\n";
    //    mario.attack(anto);
    //    cout << mario.toStr();
    //    cout << anto.toStr();
}

MajorCharacter Controller::pgInitialization(View curview){
   char name[500];
   int c;
   Pos p = {0, 0, 0, 0};
   ability ab;
   curview.print_introduction(); //Qui chiede di scrivere il nome
   move(1,2);
   getstr(name);

   curview.print_classselection(); //Qui chiedera di scrivere un carattere correispettivo alla classe

   bool corretto=false;
   int soldiagg=0;
   while(!corretto){
        c=getchar();
        switch(c){
        case 97:  //a -> ingeneria HIGH FORZA E VITA, LOW RESTO
            ab.setLife(20);
            ab.setStrength(5);
            ab.setDefense(2);
            corretto=true;
        break;
        case 98: //b-> lingue  HIGH DEF E VITA,LOW RESTO
            ab.setLife(20);
            ab.setStrength(2);
            ab.setDefense(5);
            corretto=true;
        break;
        case 99: //c-> scienze Tutto nedio
            ab.setLife(15);
            ab.setStrength(3);
            ab.setDefense(3);

            corretto=true;
        break;
        case 100: //d->umanistiche HIGH VITA E SOLDI,LOW RESTO

            ab.setLife(20);
            ab.setStrength(2);
            ab.setDefense(2);
            soldiagg=50;

            corretto=true;
        break;
        case 101: //e->fuoricorso LOW TUTTO INIZI CON UN DEBITO
            ab.setLife(10);
            ab.setStrength(1);
            ab.setDefense(1);
            soldiagg=-50;

            corretto=true;
        break;
        case 102: //f->medicina HIGH FORZA E DEF,LOW RESTO
            ab.setLife(10);
            ab.setStrength(5);
            ab.setDefense(5);
            corretto=true;
        break;
        case 112://Debug, tutte le statistiche a 99
            ab.setLife(200);
            ab.setStrength(99);
            ab.setDefense(99);
            soldiagg=1000;
            corretto=true;
            break;

    }
   }
   //MajorCharacter::MajorCharacter(string n, ability s, Pos p, string d, Follower* f)
   string nome(name);
   MajorCharacter pg(nome,ab,p,"",NULL);

    pg.setMoney(soldiagg);
    pg.setCurWeapon(new Item("Spada di legno",0,WEAPON));
    pg.setCurArmor(new Item("Armatura di Immaginazione",0,ARMOR));
    pg.getCurArmor()->setSym("a");
    pg.getCurWeapon()->setSym("w");
    pg.setSym("@");
    pg.setFullStats(ab);

return pg;
}
