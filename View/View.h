
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
        void stampaoutputMappa(Mappa* CurLevel);
        void stampastoria(queue<char*>* narrative);
        void stampaequip(string s);
        void clearoutputMappa();

};


#endif //VIEW_H
