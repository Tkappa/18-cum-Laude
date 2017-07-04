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
    anto.setSym("x");
    //    pg.setFollower(f);
    //curMap.assegnaPosIniziale(anto);
    curMap->assignInizialPosition_toPlayer(punt_pg);

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
    vista.print_nameAndStats(pg);
    vista.print_outputMap(curMap);
    narrative.push("Questa sarà una grande avventura!");
    vista.print_narrative(&narrative);
    //    vista.stampaequip(pg.getDesc());
    refresh();


    char b[40];
    char a[80];
    int l1;
    int l2;
    Pos p1;
    Pos p2;
    //    FILE* caratteri = fopen("data/getch", "w");
    //    if (caratteri == NULL) vista.stampaequip("NULL");
    //Questo � un abbozzo di movimento
    int c;
    int mov;
    while (1) {
        c = getch();
        //std::cout<<c;
        p1 = pg.getPos();
        p2 = anto.getPos();
        l1 = pg.getStats().getLife();
        l2 = anto.getStats().getLife();
        sprintf(b, "%c: %d %d %d %d\t%c: %d %d %d %d", pg.getSym(), p1.mapX, p1.mapY, p1.stanzX, p1.stanzY, anto.getSym(), p2.mapX, p2.mapY, p2.stanzX, p2.stanzY);
        sprintf(a, "%s\t%c: %d\t%c: %d", b, pg.getSym(), l1, anto.getSym(), l2);
        //        sprintf(b, "%c: %d\n", c, c);
        //        fputs(b, caratteri);
        //        vista.stampaequip(b);
        //vista.stampaequip(a);
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
                sprintf(b,"Premuto \'t\', dir: %d",mov);
                //vista.stampastoria(b);
                if (curMap->mapCanMove(punt_pg, mov))
                    curMap->moveChar(punt_pg, mov);
                vista.print_outputMap(curMap);
                break;
        }
        if (c == 113)// char 'q'
            break;

    vista.print_narrative(&narrative);
    }

    refresh();
}

void Controller::testFollower() {
    Follower gino;
    cout << gino.toStr();
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
