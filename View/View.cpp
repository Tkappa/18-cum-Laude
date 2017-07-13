#include "View.h"

#ifdef __APPLE__ && __MACH__
    #include <ncurses.h>
#else
    #include <ncurses/curses.h>
#endif

#include <stdlib.h>
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
#define BUY 4

View::View(){

    //Per adesso non ï¿½ ancora resizible quindi i valori sono costanti
    refresh();


    int height = 2;
	int width = COLS;
	int starty = 0;
	int startx = 0;

    nameAndStats=newwin(height,width,starty,startx+1);

    height=(LINES-7);
    starty=2;
    outputMap=newwin(height,width,starty,startx);
    help=newwin(height,width,starty,startx);

    height=5;
    starty=LINES-5;
    narrative=newwin(height,width,starty,startx+1);

    height=5;
    starty=LINES-5;
    winventory=newwin(height,width,starty,startx);

    height=5;
    starty=LINES/2-3;
    width/=2;
    width+=20;
    startx=width-20-width/2;
    death=newwin(height,width,starty,startx);
    victory=newwin(height,width,starty,startx);
    exitconfirmation=newwin(height,width,starty,startx);

    height=2;
    starty=0;
    width=COLS;
    startx=1;

    introduction=newwin(height,width,starty,startx);

    starty=height;
    height=10;
    classselection=newwin(height,width,starty,startx);



}

void View::print_introduction(){
    werase(introduction);
    string message="Oh giovane ignaro diplomando , in cosa ti sei cacciato? Qual'e' il tuo nome?";

    wprintw(introduction,message.c_str());
    wmove(introduction,1,0);
    message=">";
    wmove(introduction,1,0);
    wprintw(introduction,message.c_str());
    wrefresh(introduction);


}
void View::print_classselection(){
    werase(classselection);
    string message="Tanto il tuo nome non importa piu' da oggi sarai Matricola 000052423. E in che facolta vorresti iscriverti?";
    wprintw(classselection,message.c_str());
    wmove(classselection,1,0);
    message="(a) Voglio iscrivermi a ingegnieria, non mi piace itagliano! (Alta forza di volonta e morale)";
    wprintw(classselection,message.c_str());
    wmove(classselection,2,0);
    message="(b) Voglio iscrivermi a giurisprudenza, tanto non e' a numero chiuso!(Alta Morale e concentrazione)";
    wprintw(classselection,message.c_str());
    wmove(classselection,3,0);
    message="(c) Voglio iscrivermi a scienze, mi obbligano i miei! (Tutto nella media)";
    wprintw(classselection,message.c_str());
    wmove(classselection,4,0);
    message="(d) Voglio inseguire le mie passioni (Umanistica)! (Alto morale e parti con dei CFU pagati dal papi)";
    wprintw(classselection,message.c_str());
    wmove(classselection,5,0);
    message="(e) In realta' sono fuoricorso e voglio riprendere.. (PAZZO! Tutte le statistiche al minimo e un debito di 50 CFU)";
    wprintw(classselection,message.c_str());
    wmove(classselection,6,0);
    message="(f) Voglio iscrivermi a medicina, non mi piace vivere! (Alta forza di volonta e concentrazione)";
    wprintw(classselection,message.c_str());
    wmove(classselection,7,0);
    message="Premi la lettera corrispondente alla scelta per immatricolarti";
    wprintw(classselection,message.c_str());


    wrefresh(classselection);

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
    wprintw(nameAndStats," Morale: ");
    sprintf(buffer,"%d",fullvita);
    wprintw(nameAndStats,buffer);

    wprintw(nameAndStats," (MAX: ");
    sprintf(buffer,"%d",vita);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,") Forza di volonta': ");
    sprintf(buffer,"%d",fullforza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"(");
    sprintf(buffer,"%d",forza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"+");
    sprintf(buffer,"%d",fullforza-forza);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,") Concentrazione: ");
    sprintf(buffer,"%d",fulldefen);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"(");
    sprintf(buffer,"%d",defen);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,"+");
    sprintf(buffer,"%d",fulldefen-defen);
    wprintw(nameAndStats,buffer);
    wprintw(nameAndStats,")");
    wmove(nameAndStats,1,0);
    wprintw(nameAndStats,"Arma: ");
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
    int height=5;
    int width = COLS;
	int startx = 0;
    int starty=LINES-5;
    winventory=newwin(height,width,starty,startx);
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
        case BUY:
            height=6;
            starty=(LINES/2)-5;
            startx=4;
            width=COLS-7;
            winventory=newwin(height,width,starty,startx);
            box(winventory,0,0);
            waddstr(winventory,"Benvenuto nella bottega del tutor, premi la lettera corrispondente all'oggetto per acquistarlo o k per annullare:");

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
                    strcat(stampstring," a Forza di volonta')");
                    break;
                case 2: //armatura
                    strcat(stampstring," a Concentrazione)");
                    break;
                case 4: //Pozione
                    strcat(stampstring," a Morale)");
                    break;
                }
            if(status==BUY){
                strcat(stampstring," Prezzo: ");
                sprintf(buf,"%d",(*i)->getPrice());
                strcat(stampstring,buf);
            }
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
    int cursY=1;
    while(!narrativequeue->empty()){
        char* a=narrativequeue->front();
        waddstr(narrative,a);
        wmove(narrative,cursY++,0);
        narrativequeue->pop();
    }
    wrefresh(narrative);
}

void View::print_death(p_char pgprincipale ,p_char omicida){
    box(death,0,0);
    wmove(death,1,1);
    const int  nflavour=3;
    string messaggio;
    string flavourtext[nflavour]={"I tuoi genitori devono essere molto fieri di te..","Mi dicono che al burger king stanno assumendo","Tanto non volevi veramente farla"};
    if(omicida==nullptr){
        messaggio="Hai perso tutta la tua voglia di studiare e hai abbandonato gli studi";
    }
    else{
        messaggio=omicida->getName();
        messaggio+=" ti ha convinto che forse l'università non fa per te.";
    }
    waddstr(death,messaggio.c_str());
    wmove(death,2,1);
    int c=rand()%nflavour;
    waddstr(death,flavourtext[c].c_str());

    wmove(death,3,1);
    messaggio="Premere qualsiasi tasto per terminare l'avventura...";
    waddstr(death,messaggio.c_str());
    wrefresh(death);

    }

void View::print_victory(){
box(victory,0,0);
    wmove(victory,1,1);
    const int  nflavour=3;
    string messaggio;
    messaggio="Congratulazioni , ti sei laureato!";
    waddstr(victory,messaggio.c_str());
    wmove(victory,2,1);
    messaggio="Adesso ti tocca cercare lavoro, o hai intenzione di fare la magistrale?";
    waddstr(victory,messaggio.c_str());

    wmove(victory,3,1);
    messaggio="Premere qualsiasi tasto per terminare l'avventura...";
    waddstr(victory,messaggio.c_str());
    wrefresh(victory);
}
void View::print_exitconfirmation(){
    box(exitconfirmation,0,0);
    wmove(exitconfirmation,1,1);
    string messaggio="Confermi di voler uscire? y/n";
    waddstr(exitconfirmation,messaggio.c_str());
    wrefresh(exitconfirmation);
}

void View::print_help(){
    box(help,0,0);
    int curY=2;
    wmove(help,curY,1);
    string messaggio;
    messaggio="Benvenuto in 18 e Lode! Il gioco satirico universitario.";
    curY++;
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Il tuo scopo e' sopravvivere ad ogni livello fino ad arrivare al livello 15 , dove ti aspetta la tua laurea.";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Ti puoi muovere utilizzando le freccette o wasd";
     waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="In ogni livello inizi dalle scale che portano su '<' e il tuo scopo e arrivare alle scale che portano giu '>'";
     waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Quando sei sopra una scala premi il corrispettivo tasto per usarla (> o <)";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="I livelli sono pieni di distrazioni che cercano di non farti studiare(Lettere maiuscole)e oggetti(lettere minuscole)";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Per attaccare una distrazione basta camminarci contro (Lo stesso vale per loro verso di te!)";
     waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Per raccogliere i vari oggetti dovrai premere il tasto 'l' quando ci sei sopra";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Per vedere il tuo inventario basta premere il tasto 'i'";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Per equipaggiare o usare un oggetto dovrai premere il tasto 'e'";
     waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Per buttare oggetti a terra dovrai premere il tasto 'g'";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
    messaggio="Per fare passare un turno senza fare niente premere il tasto 'o'";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Quando sarai al ricevimento con il tutor dovrai premere il tasto 't' per vedere come ti puo aiutare(Costa CFU)";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);

     messaggio="La tua vita e' il tuo Morale , quando questo scende a 0 deciderai di lasciare gli studi, perdendo";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);

     messaggio="Combatti le distrazioni usando la tua forza di volonta'";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);

     messaggio="Ti difendi dalle distazioni usando la tua concentrazione";
     waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);
     messaggio="Puoi visualizzare questa schermata in qualsiasi momento premendo il tasto 'h'";
    waddstr(help,messaggio.c_str());
    wmove(help,curY++,1);wmove(help,curY++,1);wmove(help,curY++,1);
     messaggio="Buona avventura! Premi qualsiasi tasto per continuare..";
    waddstr(help,messaggio.c_str());


    wrefresh(help);
}
