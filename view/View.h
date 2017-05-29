
#ifndef VIEW_H
#define VIEW_H

#include <ncurses/curses.h>
#include "mappa/Mappa.h"
#include "../model/pc/Character.hpp"
class View{
    protected:
        WINDOW * nomeEstat;
        WINDOW * outputMappa;
        WINDOW * storia;
        WINDOW * equip;
    public:
        View();
        void stampanomeEstat(Character &c);
        void stampaoutputMappa(Mappa livello);
        void stampastoria(string s);
        void stampaequip(string s);

};


#endif //VIEW_H
