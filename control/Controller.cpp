#include <ncurses/curses.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
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
#define USE 4


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
    head= new Map(1,1,&narrative);
    Map* curMap=head;

    //crea il personaggio principale
    ability mainpc;
    Pos p = {0, 0, 0, 0};

    //Follower gino("Gino", mainpc);
    //gino.setSym('f');
    MajorCharacter pg("Mario", mainpc, p, "Il Campione.", NULL);
    MajorCharacter anto("Antonio", mainpc, p, "L'antagonista", NULL);

    Character * punt_pg=&pg;

    //Character * punt= &pg;
    pg.setSym("@");

    punt_pg->setCurWeapon(new Item("Spada di legno",0,WEAPON));
    punt_pg->setCurArmor(new Item("Armatura di Immaginazione",0,ARMOR));
    punt_pg->getCurArmor()->setSym("a");
    punt_pg->getCurWeapon()->setSym("w");
    punt_pg->setMoney(0);

    anto.setSym("x");
    //    pg.setFollower(f);
    //curMap.assegnaPosIniziale(anto);
    curMap->assignInizialPosition_toPlayer(punt_pg);


    //cout<<"ho creato l'oggetto: "<<i->getName()<<" - valore: "<<i->getValue()<<" tipo: "<<i->getType()<<endl;



    //setup di ncurses , queste ci vogliono sempre
    initscr(); //inizializza ncurses
    clear(); //pulisce la console
    noecho(); //toglie gli input a schermo
    cbreak(); // toglie la necessita di premere invio ad ogni comando
    curs_set(0); //toglie il cursore
    keypad(stdscr, TRUE); //offre la possibilit� di usare tasti speciali (freccette etc..)

    //inizializzazione della classe view
    View vista;




    //stampa l'interfaccia utente
    vista.print_nameAndStats(punt_pg);
   // vista.print_inventory(inv.inventoryToStr());
    vista.print_outputMap(curMap);
    char iniz[500]="Questa sara' una grande avventura!";
    narrative.push(iniz);
    vista.print_narrative(&narrative);
    //    vista.stampaequip(pg.getDesc());
    refresh();



    //    FILE* caratteri = fopen("data/getch", "w");
    //    if (caratteri == NULL) vista.stampaequip("NULL");
    //Questo � un abbozzo di movimento
    int c;
    int mov;
    bool turno= true;
    while (1) {
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
            case 102:// char 'f'
                //vista.stampastoria("Premuto \'f\'");
                pg.attack(anto);
                break;
            case 116:// char 't'

                mov = pg.moveToChar(anto); //non funziona
                //vista.stampastoria(b);
                if (curMap->mapCanMove(punt_pg, mov))
                    curMap->moveChar(punt_pg, mov);
                vista.print_outputMap(curMap);
                break;
            case 105://char i
                vista.print_inventory(pg.getInventory(),SEE);
                turno = false;
                break;
            case 103://char g
                {vista.print_inventory(pg.getInventory(),DROP);
                bool finished=false;
                while(!finished){
                    c=getch();
                    if (c=='k'){finished=true;}
                    if(drop(punt_pg,c,curMap)){
                        finished=true;
                        //aggiungere a narrative " Hai buttato per terra $OGGETTO
                    }
                }
                }
                break;
            case 101://char e
                {vista.print_inventory(pg.getInventory(),EQUIP);
                bool finished=false;
                while(!finished){
                    c=getch();
                    if (c=='k'){finished=true;}
                    if(equip(punt_pg,c)){
                        finished=true;
                        //aggiungere a narrative " Hai Equipaggiato  $OGGETTO
                    }
                }
                }break;
            case 117://char e
                {vista.print_inventory(pg.getInventory(),USE);
                bool finished=false;
                while(!finished){
                    c=getch();
                    if (c=='k'){finished=true;}
                    if(use(punt_pg,c)){
                        finished=true;
                        //aggiungere a narrative " Hai Equipaggiato  $OGGETTO
                    }
                }
                }break;
            case 108://char l
                loot(punt_pg,curMap);
                break;
            case 109://char m
                vista.print_death(punt_pg);
                c=getch();
                exit(1);
                break;
        }
        if (c == 113)// char 'q'
            break;

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
                        char* bla;
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
    for (std::list<p_item>::iterator i = pg_inventorytemp.begin(); i != pg_inventorytemp.end();/* si incrementa nel body*/){
        if(tempchar==(*i)->getInventoryId()){
            std::list<p_item>::iterator new_i = i;
            ++new_i;

            (*i)->position=pg->getPos();
            p_item tempp=(*i);

            pg_inventorytemp.remove((*i));
            pg->pg_inventory.deleteItem(tempchar);
            curMap->addItem(tempp);
            i=new_i;

            return true;
        }
        else{
            ++i;
        }
    }
    return false;
    }

bool Controller::equip(p_char pg, char c){
    string tempchar="a";
    tempchar[0]=c;
    std::list<p_item> pg_inventorytemp=pg->pg_inventory.getInventory();
    for (std::list<p_item>::iterator i = pg_inventorytemp.begin(); i != pg_inventorytemp.end();/* si incrementa nel body*/){
        if(tempchar==(*i)->getInventoryId()&&((*i)->getType()==1 || (*i)->getType()==2)){
            std::list<p_item>::iterator new_i = i;
            ++new_i;


            p_item temp=(*i);
            p_item add;
            switch((*i)->getType()){
                case 1:
                    add=pg->equipWeapon(temp);
                    cout<<add->getName()<<endl;
                    break;
                case 2:
                    add=pg->equipArmor(temp);
                    break;
            }
            pg->pg_inventory.deleteItem(tempchar);
            pg->pg_inventory.addItem(add);

            i=new_i;
            return true;
        }
        else{
            ++i;
        }
    }
    return false;
}

bool Controller::use(p_char pg, char c){
    string tempchar="a";
    tempchar[0]=c;
    std::list<p_item> pg_inventorytemp=pg->pg_inventory.getInventory();
    for (std::list<p_item>::iterator i = pg_inventorytemp.begin(); i != pg_inventorytemp.end();/* si incrementa nel body*/){
        if(tempchar==(*i)->getInventoryId()&&(*i)->getType()==4){
            std::list<p_item>::iterator new_i = i;
            ++new_i;
            int life=pg->getFullStats().getLife();
            cout<<life<<endl;
            int value=(*i)->getValue();
            cout<<value<<endl;
            ability temp=pg->getFullStats();
            temp.setLife(life+value);
            pg->setFullStats(temp);
            pg->pg_inventory.deleteItem(tempchar);
            //AGGIUNGERE A NARRAZIONE "HAI BEVUTO POZIONE"
            i=new_i;
            return true;
        }
        else{
            ++i;
        }
    }
    return false;
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

p_char pgInitialization(View curview){
   //q curview.print
}
