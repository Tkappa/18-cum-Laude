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
    Mappa map(10);

    //crea il personaggio principale
    ability mainpc;
    Pos p = {0, 0, 0, 0};

    Follower gino("Gino", mainpc);
    gino.setSym('f');

    MajorCharacter pg("Mario", mainpc, p, "Il Campione.", &gino);
    MajorCharacter anto("Antonio", mainpc, p, "L'antagonista", NULL);
    //Character * punt= &pg;
    pg.setSym('@');
    anto.setSym('x');
    //    pg.setFollower(f);
    map.assegnaPosIniziale(anto);
    map.assegnaPosIniziale(gino);
    map.assegnaPosIniziale(pg);

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
    vista.stampanomeEstat(pg);
    vista.stampaoutputMappa(map);
//    vista.stampastoria("Ciao! Questa sara' una grande avventura!");
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
        p1 = pg.getPos();
        p2 = anto.getPos();
        l1 = pg.getStats().getLife();
        l2 = anto.getStats().getLife();
        sprintf(b, "%c: %d %d %d %d\t%c: %d %d %d %d", pg.getSym(), p1.mapX, p1.mapY, p1.stanzX, p1.stanzY, anto.getSym(), p2.mapX, p2.mapY, p2.stanzX, p2.stanzY);
        sprintf(a, "%s\t%c: %d\t%c: %d", b, pg.getSym(), l1, anto.getSym(), l2);
        //        sprintf(b, "%c: %d\n", c, c);
        //        fputs(b, caratteri);
        //        vista.stampaequip(b);
        vista.stampaequip(a);
        switch (c) { //se il tasto premuto � "s" oppure freccia sinistra
            case 97:// char 'a'
            case 260:// left
                //controlla se si puo muovere in quella posizione
                if (map.mapCanMove(pg, 1))
                    // e in tal caso muovilo verso la posizione
                    map.moveChar(pg, 1);
                vista.stampaoutputMappa(map);
                break;
            case 100:// char 'd'
            case 261:// right
                if (map.mapCanMove(pg, 3))
                    map.moveChar(pg, 3);
                vista.stampaoutputMappa(map);
                break;
            case 119:// char 'w'
            case 259:// su
                if (map.mapCanMove(pg, 2))
                    map.moveChar(pg, 2);
                vista.stampaoutputMappa(map);
                break;
            case 115:// char 's'
            case 258:// giu
                if (map.mapCanMove(pg, 4))
                    map.moveChar(pg, 4);
                vista.stampaoutputMappa(map);
                break;
            case 102:// char 'f'
                vista.stampastoria("Premuto \'f\'");
                pg.attack(anto);
                break;
            case 116:// char 't'
                
                mov = pg.moveToChar(anto); //non funziona
                sprintf(b,"Premuto \'t\', dir: %d",mov);
                vista.stampastoria(b);
                if (map.mapCanMove(pg, mov))
                    map.moveChar(pg, mov);
                vista.stampaoutputMappa(map);
                break;
        }
        if (c == 113)// char 'q'
            break;
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