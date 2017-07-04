#include "View.h"
#include <ncurses/curses.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <queue>
#include <iostream>
View::View(){

    //Per adesso non è ancora resizible quindi i valori sono costanti
    refresh();


    int height = 1;
	int width = COLS;
	int starty = 1;
	int startx = 0;

    nameAndStats=newwin(height,width,starty,startx+1);

    height=(LINES-7);
    starty=2;
    outputMap=newwin(height,width,starty,startx);

    height=5;
    starty=LINES-5;
    narrative=newwin(height,width,starty,startx+1);

    height=5;
    starty=LINES-5;
    inventory=newwin(height,width,starty,startx);
}

void View::print_nameAndStats(Character & c){
    //QUA SI INTERFACCIA CON PG
    const char* nomechar;
    nomechar=c.getName().c_str();
    int vita,forza,intel;
    vita=c.getStats().getLife();
    forza=c.getStats().getStrength();
    intel=c.getStats().getIntelligence();
    weapons w = c.getArmi().front();

    char buffer[3];

    attron(COLOR_PAIR(1));
    wmove(nameAndStats,0,0);
    wprintw(nameAndStats,"Nome personaggio: ");
    wprintw(nameAndStats,nomechar);
    wprintw(nameAndStats," Vita: ");
    sprintf(buffer,"%d",vita);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats," Forza: ");
    sprintf(buffer,"%d",forza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats," Intelligenza: ");
    sprintf(buffer,"%d",intel);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"  | Arma: ");
    nomechar = w.getName().c_str();
    wprintw(nameAndStats,nomechar);
    sprintf(buffer,"%d",w.getValue());
    wprintw(nameAndStats," [");
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"]");
    attroff(COLOR_PAIR(1));
    wrefresh(nameAndStats);
}
void View::print_inventory(string s){
    const char* details = s.c_str();
    box(inventory,0,0);
    mvwprintw(inventory,1,1,details);
    wrefresh(inventory);
}
void View::print_outputMap(Map * CurLevel){
    box(outputMap,0,0);
    wmove(outputMap,1,3);
    int colMap,rigMap,colSt,rigSt,cursX,cursY,cursBaseY;
    cursBaseY=1;
    cursX=3;
    cursY=1;
    char buffer[3];
    //stampa la struttura dati della mappa
    for(rigMap=0;rigMap<mapHeight;rigMap++){
        for(colMap=0;colMap<mapLenght;colMap++){
            if(CurLevel->roomExplored(colMap,rigMap)){
                for(rigSt=0;rigSt<roomHeight;rigSt++){
                    for(colSt=0;colSt<roomLenght;colSt++){
                        char stamp=CurLevel->getMapChar(colMap,rigMap,colSt,rigSt);
                            waddch(outputMap,stamp);
                    }
                    cursY++;
                    wmove(outputMap,cursY,cursX);
                 }
            }
            cursY=cursBaseY;
            cursX=cursX+roomLenght;
            wmove(outputMap,cursY,cursX);
        }
        cursX=3;
        cursBaseY+=roomLenght;
        cursY=cursBaseY;
        wmove(outputMap,cursY,cursX);
    }

    //Stampa tutti i personaggi "che si muovono" cosi non modificano la struttura dati
    std::list<p_char> pers;
    pers=CurLevel->getList();
    int printx,printy;
    for (std::list<p_char>::iterator i = pers.begin(); i != pers.end(); ++i){
            //std::cout<<"Sto stampando "<<*i<<" con simbolo:"<<(*i)->getSym()<<"\n";
            printy=3+(*i)->pos.mapY*roomHeight+(*i)->pos.stanzY;
            printx=1+(*i)->pos.mapX*roomLenght+(*i)->pos.stanzX;
            wmove(outputMap,printx,printy);
            waddstr(outputMap,(*i)->getSym().c_str());
    }
    wrefresh(outputMap);
}
void View::clearoutputMap(){
    werase(outputMap);
      }
void View::print_narrative(queue<char*>* narrativequeue){
    werase(narrative);
    int cursY=0;
    while(!narrativequeue->empty()){
        char* a=narrativequeue->front();
        waddstr(narrative,a);
        cursY++;
        wmove(narrative,cursY,0);
        narrativequeue->pop();
    }
    wrefresh(narrative);
}

