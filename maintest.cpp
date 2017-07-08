/*
#include <ncurses/curses.h>
#include "View/Mappa/Mappa.h"
#include "View/View.h"
#include "model/pc/Item.h"
#include "model/pc/inventory.h"
#include <iostream>

#include <time.h>
#include <cstdlib>
using namespace std;

//Per farlo funzionare bisogna scaricare la libreria ncurses e mettere tra le opzioni del --->LINKER<--- "-lncurses", vedi http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

//commentato tutto per non dare conflitti con altri eventuali main
int main(int argc, char *argv[])
{
    //crea il random
    time_t t;
    srand((unsigned)time(&t));

    Item *i= Item::randomItem(2);
    Item *l= Item::randomItem(2);
    Item *m= Item::randomItem(2);
    cout<<"ho creato l'oggetto: "<<i->getName()<<" - valore: "<<i->getValue()<<" tipo: "<<i->getType()<<endl;

    inventory inv=inventory();

    inv.addItem(*i);
    inv.addItem(*l);
    inv.addItem(*m);

    cout<<"Inventario iniziale: "<<endl<<inv.inventoryToStr()<<endl;

    cout<<"Arma da eliminare: ";
    int n;
    cin>>n;
    inv.deleteItem(n);


    cout<<"Inventario finale: "<<endl<<inv.inventoryToStr()<<endl;


    //crea la struttura dati con 3 stanze base
    /*Mappa pippo(10);

    //crea il personaggio principale
    pers giovanni;
    pers * punt= &giovanni;
    giovanni.nome='@';
    pippo.assegnaPosIniziale(punt);

    //setup di ncurses , queste ci vogliono sempre
    initscr(); //inizializza ncurses
    clear(); //pulisce la console
	noecho(); //toglie gli input a schermo
	cbreak(); // toglie la necessita di premere invio ad ogni comando
	curs_set(0); //toglie il cursore
	keypad(stdscr, TRUE); //offre la possibilità di usare tasti speciali (freccette etc..)

	//inizializzazione della classe view
    View prova;
    //stampa l'interfaccia utente
    prova.stampanomeEstat();
    prova.stampaoutputMappa(pippo);
    prova.stampastoria();
    prova.stampaequip();
    refresh();


    //Questo è un abbozzo di movimento
    int c;
    while(1){
	    c = getch();
		switch(c)

		{	//se il tasto premuto è "s" oppure freccia sinistra
		    case 97:
            case 260:
                //controlla se si puo muovere in quella posizione
                if(pippo.mapCanMove(punt,1))
                    // e in tal caso muovilo verso la posizione
                   pippo.moveChar(punt,1);
                prova.stampaoutputMappa(pippo);
                break;
		    case 100:
            case 261:
		        if(pippo.mapCanMove(punt,3))
                    pippo.moveChar(punt,3);
                prova.stampaoutputMappa(pippo);
                break;
		    case 119:
            case 259:
		        if(pippo.mapCanMove(punt,2))
                    pippo.moveChar(punt,2);
				prova.stampaoutputMappa(pippo);
				break;
			case 115:
            case 258:
			    if(pippo.mapCanMove(punt,4))
                    pippo.moveChar(punt,4);
				prova.stampaoutputMappa(pippo);
				break;
	}
	if(c == 112)
			break;
	}

	refresh();

    return 0;
}
*/
