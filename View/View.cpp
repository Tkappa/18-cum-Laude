#include "View.h"
#include <ncurses/curses.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <iostream>
View::View(){
    refresh();
    int height = 1;
	int width = COLS;
	int starty = 1;
	int startx = 0;
    refresh();
    nomeEstat=newwin(height,width,starty,startx+1);
    height=(LINES-7);
    starty=2;
    outputMappa=newwin(height,width,starty,startx);
    height=1;
    starty=LINES-5;
    storia=newwin(height,width,starty,startx+1);
    height=4;
    starty=LINES-4;
    equip=newwin(height,width,starty,startx);
}

void View::stampanomeEstat(Character & c){
    //QUA SI INTERFACCIA CON PG
    const char* nomechar;
    nomechar=c.getName().c_str();
    int vita,forza,intel;
    vita=c.getStats().getLife();
    forza=c.getStats().getStrength();
    intel=c.getStats().getIntelligence();
    weapons w = c.getArmi().front();
    
    char buffer[3];
    //box(nomeEstat,0,0);

    attron(COLOR_PAIR(1));
    wmove(nomeEstat,0,0);
    wprintw(nomeEstat,"Nome personaggio: ");
    wprintw(nomeEstat,nomechar);
    wprintw(nomeEstat," Vita: ");
//    wprintw(nomeEstat,itoa(vita,buffer,10));
    sprintf(buffer,"%d",vita);
    wprintw(nomeEstat,buffer);
    wprintw(nomeEstat," Forza: ");
//    wprintw(nomeEstat,itoa(forza,buffer,10));
    sprintf(buffer,"%d",forza);
    wprintw(nomeEstat,buffer);
    wprintw(nomeEstat," Intelligenza: ");
//    wprintw(nomeEstat,itoa(intel,buffer,10));
    sprintf(buffer,"%d",intel);
    wprintw(nomeEstat,buffer);
    wprintw(nomeEstat,"  | Arma: ");
    nomechar = w.getName().c_str();
    wprintw(nomeEstat,nomechar);
    sprintf(buffer,"%d",w.getValue());
    wprintw(nomeEstat," [");
    wprintw(nomeEstat,buffer);
    wprintw(nomeEstat,"]");
    attroff(COLOR_PAIR(1));
    wrefresh(nomeEstat);
}
void View::stampaequip(string s){
    const char* details = s.c_str();
    box(equip,0,0);
    mvwprintw(equip,1,1,details);
    wrefresh(equip);
}
void View::stampaoutputMappa(Mappa livello){
    box(outputMappa,0,0);
    wmove(outputMappa,1,3);
    int colMap,rigMap,colSt,rigSt,cursX,cursY,cursBaseY;
    cursBaseY=1;
    cursX=3;
    cursY=1;
    char buffer[3];
    //stampa la struttura dati della mappa
    for(rigMap=0;rigMap<altezzaMappa;rigMap++){
        for(colMap=0;colMap<lunghezzaMappa;colMap++){
            if(livello.stanzaEsplorata(colMap,rigMap)){
                for(rigSt=0;rigSt<altezzaStanza;rigSt++){
                    for(colSt=0;colSt<lunghezzaStanza;colSt++){
                        char stamp=livello.getMapChar(colMap,rigMap,colSt,rigSt);
                            waddch(outputMappa,stamp);
                    }
                    cursY++;
                    wmove(outputMappa,cursY,cursX);
                 }
            }
            cursY=cursBaseY;
            cursX=cursX+lunghezzaStanza;
            wmove(outputMappa,cursY,cursX);
        }
        cursX=3;
        cursBaseY+=altezzaStanza;
        cursY=cursBaseY;
        wmove(outputMappa,cursY,cursX);
    }

    //Stampa tutti i gli oggetti "che si muovono" cosi non modificano la struttura dati
    std::list<p_char> oggetti;
    int printx,printy;
    oggetti=livello.getList();
    for (std::list<p_char>::iterator i = oggetti.begin(); i != oggetti.end(); ++i){
            printy=3+(*i)->pos.mapY*altezzaStanza+(*i)->pos.stanzY;
            printx=1+(*i)->pos.mapX*lunghezzaStanza+(*i)->pos.stanzX;
            wmove(outputMappa,printx,printy);
            waddch(outputMappa,(*i)->getSym());
    }
    wrefresh(outputMappa);
}
void View::stampastoria(string s){
    const char* cose = s.c_str();
    mvwprintw(storia,0,0,cose);
    wrefresh(storia);
}

