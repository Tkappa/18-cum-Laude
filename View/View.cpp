#include "View.h"
#include <ncurses/curses.h>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <queue>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define SEE 1
#define DROP 2
#define EQUIP 3
#define USE 4

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
    winventory=newwin(height,width,starty,startx);
}

void View::print_nameAndStats(p_char c){
    //QUA SI INTERFACCIA CON PG
    werase(nameAndStats);
    const char* nomechar;
    nomechar=c->getName().c_str();
    int vita,forza,defen,fullvita,fullforza,fulldefen,cfu;
    fullvita=c->getFullStats().getLife();
    fullforza=c->getFullStats().getStrength();
    fulldefen=c->getFullStats().getDefense();
    vita=c->getBaseStats().getLife();
    forza=c->getBaseStats().getStrength();
    defen=c->getBaseStats().getDefense();
    cfu=c->getMoney();
    //Item w = c.getObject().front();

    char buffer[3];

    attron(COLOR_PAIR(1));
    wmove(nameAndStats,0,0);
    wprintw(nameAndStats,"Nome: ");
    wprintw(nameAndStats,nomechar);
    wprintw(nameAndStats," Vita: ");
    sprintf(buffer,"%d",fullvita);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats," Forza: ");
    sprintf(buffer,"%d",fullforza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"(");
    sprintf(buffer,"%d",forza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"+");
    sprintf(buffer,"%d",fullforza-forza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,") Difesa: ");
    sprintf(buffer,"%d",fulldefen);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"(");
    sprintf(buffer,"%d",defen);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"+");
    sprintf(buffer,"%d",fulldefen-defen);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,")| Arma: ");
    wprintw(nameAndStats,c->getCurWeapon()->getName().c_str());
    wprintw(nameAndStats,"| Armatura: ");
    wprintw(nameAndStats,c->getCurArmor()->getName().c_str());
    wprintw(nameAndStats,"| CFU: ");
    sprintf(buffer,"%d",cfu);
    wprintw(nameAndStats,buffer);
    attroff(COLOR_PAIR(1));
    wrefresh(nameAndStats);
}

void View::print_inventory(inventory pg_inventoryfull,int status){

    werase(winventory);
    wmove(winventory,0,3);
    switch(status){
        case SEE:
            waddstr(winventory,"Questo e' il tuo inventario:");
            break;
        case DROP:
            waddstr(winventory,"Stai per buttare via un oggetto, premi la lettera corrispondente per mollarlo, oppure k per annullare:");
            break;
        case EQUIP:
            waddstr(winventory,"Stai per equipaggiare un oggetto, premi la lettera corrispondente per equipaggiarlo, oppure k per annullare:");
            break;
        case USE:
            waddstr(winventory,"Stai per usare una pozione, premi la lettera corrispondente per usarla, oppure k per annullare:");

            break;

    }
    int cursX=3;
    int cursY=1;
    char stampstring[500]="";
    char buf[5];
    std::list<p_item> pg_inventory=pg_inventoryfull.getInventory();
    for (std::list<p_item>::iterator i = pg_inventory.begin(); i != pg_inventory.end(); ++i){
            strcpy(stampstring,(*i)->getInventoryId().c_str());
            strcat(stampstring,"|");
            strcat(stampstring,(*i)->getName().c_str());
            strcat(stampstring,"(+");
            sprintf(buf,"%d",(*i)->getValue());
            strcat(stampstring,buf);
            switch((*i)->getType()){
                case 1: //arma
                    strcat(stampstring," a Forza)");
                    break;
                case 2: //armatura
                    strcat(stampstring," a Difesa)");
                    break;
                case 4: //Pozione
                    strcat(stampstring," a Vita)");
                    break;
                }
            //cout<<"sto stampando l'inventario : "<<stampstring<<endl;

            wmove(winventory,cursY,cursX);
            waddstr(winventory,stampstring);
            cursY++;
            if(cursY==5){
                cursX=60;
                cursY=1;
            }

    }
    wrefresh(winventory);
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


    std::list<p_char> pers;
    pers=CurLevel->getListChar();
    int printx,printy;
    //Stampa tutti gli oggetti
    std::list<p_item> items;
    items=CurLevel->getListItem();
    for (std::list<p_item>::iterator i = items.begin(); i != items.end(); ++i){
            //std::cout<<"Sto stampando "<<*i<<" con simbolo:"<<(*i)->getSym()<<"\n";
            printy=3+(*i)->position.mapY*roomHeight+(*i)->position.stanzY;
            printx=1+(*i)->position.mapX*roomLenght+(*i)->position.stanzX;
            wmove(outputMap,printx,printy);
            waddstr(outputMap,(*i)->getSym().c_str());
    }

    //Stampa tutti i personaggi "che si muovono" cosi non modificano la struttura dati
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

