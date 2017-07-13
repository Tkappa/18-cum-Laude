#ifdef __APPLE__ && __MACH__
    #include <ncurses.h>
#else
    #include <ncurses/curses.h>
#endif

#include "../environment.hpp"
#include "../model/pc/Item.hpp"
#include "../model/pc/Character.hpp"
#include "../model/pc/MajorCharacter.hpp"
#include "../view/mappa/Mappa.h"
#include "../view/View.h"
#include "Controller.h"



using namespace std;

Controller::Controller(){}

void Controller::launch() {
    //Crea la componente random del gioco
    time_t t;
    srand((unsigned) time(&t));

    //Crea la struttura iniziale da cui partirà il gioco
    Map* head;
    head= new Map(1,0,&narrative,open_day);
    Map* curMap=head;

    //setup di ncurses , queste ci vogliono sempre
    initscr(); //inizializza ncurses
    clear(); //pulisce la console
    cbreak(); // toglie la necessita di premere invio ad ogni comando
    curs_set(0); //toglie il cursore
    keypad(stdscr, TRUE); //offre la possibilita di usare tasti speciali (freccette etc..)


    //Controlla se il terminale è abbastanza grande da poter stampre il gioco correttamente
    if(COLS<120||LINES<30){
        endwin();
        cout<<"Si prega di ingrandire il terminale in modo che la larghezza sia 120 o piu' e la l'altezza 30 o piu' (tasto destro sul terminale , proprieta', layout, dimensioni finestra)";
        exit(1);
    }

    //inizializzazione della classe view
    View vista;

    //creazione del personaggio
    MajorCharacter pg=pgInitialization(vista);
    p_char punt_pg=&pg;
    curMap->assignInizialPosition_toPlayer(punt_pg);

    noecho(); //toglie gli input a schermo

    //Stampa il gioco
    vista.print_nameAndStats(punt_pg);
    vista.print_outputMap(curMap);
    char iniz[500]="Questa sara' una grande avventura!";
    narrative.push(iniz);
    vista.print_narrative(&narrative);
    refresh();

    //Viene visualizzato il tutorial iniziale
    vista.print_help();
    getch();
    vista.print_outputMap(curMap);

    //Movimento e handling Input
    int c;
    bool turno= true;
    Direction player_dir;

    while (1) {

        player_dir=stop;
        c = getch();

        switch (c) {

            //------MOVIMENTI-------
            case 97:// char 'a'
            case 260:// left
                //controlla se si puo muovere in quella posizione
                if (curMap->mapCanMove(punt_pg, 1))
                    // Imposta il movimento del personaggio verso quella posizione
                    player_dir=Direction::left;
                break;


            case 100:// char 'd'
            case 261:// right
                if (curMap->mapCanMove(punt_pg, 3))
                    player_dir=Direction::right;
                break;


            case 119:// char 'w'
            case 259:// su
                if (curMap->mapCanMove(punt_pg, 2))
                    player_dir=Direction::up;
                break;


            case 115:// char 's'
            case 258:// giu
                if (curMap->mapCanMove(punt_pg, 4))
                    player_dir=Direction::down;
                break;

            //-----CAMBIO LIVELLO----

            case 62:{//char >
                pers stairs=curMap->getStairsDown();
                //Controlla se il personaggio è nello stessa posizione della scala
                if (stairs.pos.mapX==pg.getPos().mapX&&stairs.pos.mapY==pg.getPos().mapY && stairs.pos.stanzX==pg.getPos().stanzX && stairs.pos.stanzY==pg.getPos().stanzY){
                    //In tal caso
                    curMap=curMap->nextMap();
                    curMap->assignInizialPosition_toPlayer(punt_pg);
                }
                vista.clearoutputMap();
                }
                break;
            case 60://char <
                {
                pers stairs=curMap->getStairsUp();
                if (stairs.pos.mapX==pg.getPos().mapX&&stairs.pos.mapY==pg.getPos().mapY && stairs.pos.stanzX==pg.getPos().stanzX && stairs.pos.stanzY==pg.getPos().stanzY){
                    //Controlla se il personaggio sta cercando di uscire dal primo livello
                    if(curMap->getNLevel()==1){
                        //Fa finire il gioco( Lo considera come scappato)
                        vista.print_death(punt_pg);
                        c=getch();
                        exit(1);
                    }
                    else{
                    curMap=curMap->prevMap();
                    stairs=curMap->getStairsDown();
                    mapPos x=stairs.pos;
                    curMap->assingPosition(punt_pg,x.mapX,x.mapY,x.stanzX,x.stanzY);
                    }
                }
                vista.clearoutputMap();
                }
                break;

            //----Varie azioni----


            case 111://char o (salta turno)
                break;


            case 104: //char h (mostra help)
                vista.print_help();
                turno=false;
                break;

            case 105://char i ( visualizza l'inventario
                vista.print_inventory(pg.getInventory(),SEE);
                turno = false;
                break;

            case 116://char t ( schermata di acquisto)
                //Controlla se è un negozio e gestisce la scelta dell'acquisto
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
                }}
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
                //Controlla la condizione di vittoria, e in tal caso fa finire il gioco
                if(punt_pg->getCurWeapon()->getName()=="Laurea"){
                    vista.print_victory();
                    c=getch();
                    exit(1);
                }
                }break;



            case 108://char l raccoglie l'oggetto da terra
                loot(punt_pg,curMap);
                break;


#ifdef DEBUG
            //Tasti addizionali di debug
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
#endif // DEBUG
        }

        if (c == 113){// char 'q'  per uscire
            vista.print_exitconfirmation();
            c=getch();
            if(c=='y'||c=='Y'){
                break;
            }

        }

    //Se l'azione scelta comporta l'avanzamento di un turno , lo esegue
    if(turno){
        turn(punt_pg,curMap,player_dir,vista);
        if(!punt_pg->isAlive()){
            //Se il personaggio è morto esce dal gioco ( Il messaggio di morte è mostrato dentro il combat)
            getch();
            break;
        }
        vista.print_narrative(&narrative);
        vista.print_nameAndStats(punt_pg);
        vista.print_outputMap(curMap);

        }
    turno=true;
    }

}

void Controller::loot(p_char pg, Map* curMap){
    //Prende la posizione del personaggio
    mapPos pgpos=pg->getPos();

    std::list<p_item> items=curMap->objectList;

    //Scorre la lista di tutti gli oggetti nella mappa attuale per vedere se c'è un match
    for (std::list<p_item>::iterator i = items.begin(); i != items.end();/*si incementa durante il ciclo*/){
        if(pgpos.mapX==(*i)->position.mapX && pgpos.mapY==(*i)->position.mapY &&  pgpos.stanzX==(*i)->position.stanzX &&  pgpos.stanzY==(*i)->position.stanzY){
            //Se c'è un match crea un nuovo iteratore e lo mette allo step successivo cosi può cancellare tranquillamente
            std::list<p_item>::iterator new_i = i;
            ++new_i;

            //mette il puntatore corrente in una variabile temporanea
            p_item temp=*i;

            //Se sono soldi li aggiunge senza problemi ai CFU del personaggio
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
                //Altrimenti prima controlla se c'è abbastanza spazio cercando di aggiungerlo all'inventario
                if(pg->pg_inventory.addItem(temp)){
                    //Se ritona vero lo ha già aggiunto all'inventario , quindi si più eliminare
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

                    //Altrimenti passa a quello successivo e informa il giocatore che ha l'inventario pieno
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
    //Aggiorna la lista della mappa con quella utilizzata localmente
    curMap->objectList=items;
}

bool Controller::drop(p_char pg,char c,Map* curMap){
    string tempchar="a";
    tempchar[0]=c;

    std::list<p_item> pg_inventorytemp=pg->pg_inventory.getInventory();

    //Prova ad eliminare l'oggetto corrispettivo al carattere passato per paramentro
    p_item tempp=pg->pg_inventory.deleteItem(tempchar);

    if(tempp!=nullptr){
        //Se ritorna un puntatore , all'ora l'oggetto e' stato eliminato e quindi si puo' aggiungere alla mappa
        tempp->position=pg->getPos();
        curMap->addItem(tempp);
        return true;
    }
    //Altrimenti un carattere incorretto e' stato passato quindi ritorno false
    return false;
    }

bool Controller::equip(p_char pg, char c){
    //Stringa per controllare l'id
    string tempchar="a";
    tempchar[0]=c;


    char* msg= new char[500];

    bool usedpotion=false;


    std::list<p_item> pg_inventorytemp=pg->pg_inventory.getInventory();
    //Controllo tutto l'inventario
    for (std::list<p_item>::iterator i = pg_inventorytemp.begin(); i != pg_inventorytemp.end();++i){
        //Se c'è nella lista
        if(tempchar==(*i)->getInventoryId()&&((*i)->getType()!=3)){

            p_item temp=(*i);
            p_item add;

            switch((*i)->getType()){
                case 1:{
                    //In caso sia un armma
                    add=pg->equipWeapon(temp);

                    strcpy(msg,"Hai equipaggiato ");
                    strcat(msg,temp->getName().c_str());
                    strcat(msg, " come arma!");
                }
                    break;
                case 2:{
                    //In caso sia un'armatura
                    add=pg->equipArmor(temp);

                    strcpy(msg,"Hai equipaggiato ");
                    strcat(msg,temp->getName().c_str());
                    strcat(msg, " come armatura!");
                }
                    break;

                case 4:
                    //In caso sia una pozione

                    //Prendo vita base che verra utilizzato come limite massimo e vita full che e' la vita attuale
                    int curlife=pg->getFullStats().getLife();
                    int maxlife=pg->getBaseStats().getLife();
                    int value=(*i)->getValue();

                    //Prendo le abilita di pg in modo da poterle modificare
                    ability temp=pg->getFullStats();


                    curlife+=value;

                    //dif serve nella stampa dopo e contiene quanto ha curato
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

            narrative.push(msg);

            //Si elimina l'oggetto selezionato dall'inventario
            pg->pg_inventory.deleteItem(tempchar);

            //Se non si è usata una pozione allora l'elemento selezionato è stato equipaggiato , e bisogna aggiungere all'inventario l'elemento vecchio
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
    //Se l'elemento selezionato esiste
    if(selectedItem!=nullptr){

        int moneyafterbought=(pg->getMoney())-(selectedItem->getPrice());
        //Controllo che ci siano abbastanza soldi
        if(moneyafterbought>=0){
            //Controllo che ci sia abbastanza spazio nell'inventario
            if(pg->pg_inventory.getSize()<8){
                //Allora aggiungo l'oggetto comprato e aggiorno i soldi
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
            ab.setLife(30);
            ab.setStrength(7);
            ab.setDefense(3);
            corretto=true;
        break;
        case 98: //b-> lingue  HIGH DEF E VITA,LOW RESTO
            ab.setLife(30);
            ab.setStrength(3);
            ab.setDefense(7);
            corretto=true;
        break;
        case 99: //c-> scienze Tutto nedio
            ab.setLife(20);
            ab.setStrength(5);
            ab.setDefense(5);

            corretto=true;
        break;
        case 100: //d->umanistiche HIGH VITA E SOLDI,LOW RESTO

            ab.setLife(30);
            ab.setStrength(3);
            ab.setDefense(3);
            soldiagg=50;

            corretto=true;
        break;
        case 101: //e->fuoricorso LOW TUTTO INIZI CON UN DEBITO
            ab.setLife(15);
            ab.setStrength(1);
            ab.setDefense(1);
            soldiagg=-50;

            corretto=true;
        break;
        case 102: //f->medicina HIGH FORZA E DEF,LOW RESTO
            ab.setLife(15);
            ab.setStrength(7);
            ab.setDefense(7);
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
   MajorCharacter pg(nome,ab);

    pg.setMoney(soldiagg);
    pg.setCurWeapon(new Item("Spada di legno",0,WEAPON));
    pg.setCurArmor(new Item("Armatura di Immaginazione",0,ARMOR));
    pg.getCurArmor()->setSym("a");
    pg.getCurWeapon()->setSym("w");
    pg.setSym("@");
    pg.setFullStats(ab);

return pg;
}

void Controller::turn(p_char player,Map* curMap,int player_direction,View vista){

    //----Azione del giocatore----
    bool playerattacked=false;
    std::list<p_char>:: iterator eliminatore;
    std::list<p_char>:: iterator enemy=curMap->characterList.begin();

    //Controlla se il giocatore sta per toccare qualche mostro nella lista
    while(enemy!=curMap->characterList.end()){
        if ((*enemy)->getSym() != player->getSym()) {
                if(player->willCollide((*enemy),player_direction)){
                    //In tal caso falli combattere
                    int combatoutput=combat(player,(*enemy));
                    if(combatoutput==1){
                        //Ha ucciso il mostro
                        char* msg=new char [500];
                        strcpy(msg,"Hai sconfitto ");
                        strcat(msg,(*enemy)->getName().c_str());
                        narrative.push(msg);

                        eliminatore=enemy++;
                        curMap->characterList.erase(eliminatore);

                    }
                    else ++enemy;
                    playerattacked=true;
                }
                else ++enemy;
    }
    else ++enemy;
    }
    //Se il giocatore non ha attaccato allora si deve muovere
    if(!playerattacked){
        int player_dir=player_direction;
        curMap->moveChar(player, player_dir);
    }


    //-----Azione degli NPC----

    enemy=curMap->characterList.begin();

    bool enemyattacked=false;

    while(enemy!=curMap->characterList.end()){
        if ((*enemy)->getSym() != player->getSym()) {
            enemyattacked=false;

            //Imposta la direzione in cui dovrebbe andare il mostro
            int enemy_direction = (*enemy)->moveToChar(player, curMap->getRoomForCoord((*enemy)->pos.mapX, (*enemy)->pos.mapY));

            //Aggiunge un elemento di casualita, cosi che il mostro si muova a caso ogni tanto
            int noise=rand()%100;
            if(noise>70){
                enemy_direction=rand()%5;
            }

            if((*enemy)->willCollide(player,enemy_direction)){
                    //Se il mostro incontra il giocatore falli combattere
                    int combatoutput=combat((*enemy),player);
                    if(combatoutput==1){

                        //In questo caso il giocatore e' morto
                        vista.print_narrative(&narrative);
                        vista.print_nameAndStats(player);
                        vista.print_death(player,(*enemy));

                    }
                    enemyattacked=true;
                }
            //Se il nemico non ha attaccato allora vuol dire che si deve muovere
            if(!enemyattacked){

                int enemy_dir=enemy_direction;

                if(curMap->mapCanMove((*enemy), enemy_dir))
                    {curMap->moveChar((*enemy), enemy_dir);}
            }

        }
        ++enemy;

}}

int Controller::combat(p_char attacker, p_char defender){

    int defHP,attSTR,defSTR,defDEF;

    defHP=defender->getFullStats().getLife();

    defSTR=defender->getFullStats().getStrength();
    defDEF=defender->getFullStats().getDefense();

    attSTR=attacker->getFullStats().getStrength();

    //Aggiunge un elemento di casualita'
    int diceroll=rand()%20+1;

    int newattSTR;

    char* tipoattacco=new char[500];

    if(diceroll<2){
        strcpy(tipoattacco,"Fallimento critico! ");
        newattSTR=0;
    }
    else if(diceroll<16){
        strcpy(tipoattacco,"Attacco normale! ");
        newattSTR=attSTR-defDEF;

    }
    else if(diceroll<20){
        strcpy(tipoattacco,"Attacco potente! ");
        newattSTR=attSTR-(defDEF/3);
    }
    else if(diceroll==20){
        strcpy(tipoattacco,"Colpo critico! ");
        newattSTR=attSTR-defDEF/5;
    }



    if(newattSTR<0) newattSTR=0;

    int defNewHp;

    defNewHp=defHP-newattSTR;

    ability def_temp;

    def_temp.setLife(defNewHp);
    def_temp.setStrength(defSTR);
    def_temp.setDefense(defDEF);
    defender->setFullStats(def_temp);

    char* str= new char[400];

    char buf[10];
    strcpy(str,tipoattacco);
    strcat(str,attacker->getName().c_str());
    strcat(str," ha attaccato ");
    strcat(str,defender->getName().c_str());
    strcat(str," e ha inflitto ");
    sprintf(buf,"%d",newattSTR);
    strcat(str,buf);
    strcat(str," danni. (Att:");
    sprintf(buf,"%d",attSTR);
    strcat(str,buf);
    strcat(str,"- Dif:");
    sprintf(buf,"%d",defDEF);
    strcat(str,buf);
    strcat(str,")");

    narrative.push(str);

    if(defNewHp<=0){
        defender->setAlive(false);
        //difensore morto
        return 1;
    }
    //nessuno è morto
    return 0;

}
