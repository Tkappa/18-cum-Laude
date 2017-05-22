
#ifndef VIEW_H
#define VIEW_H

#include <curses.h>
#include "Mappa/Mappa.h"
class View{
    protected:
        WINDOW * nomeEstat;
        WINDOW * outputMappa;
        WINDOW * storia;
        WINDOW * equip;
    public:
        View();
        void stampanomeEstat();
        void stampaoutputMappa(Mappa livello);
        void stampastoria();
        void stampaequip();

};


#endif //VIEW_H
