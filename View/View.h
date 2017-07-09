
#ifndef VIEW_H
#define VIEW_H

#ifdef __APPLE__ && __MACH__
    #include <ncurses.h>
#else
    #include <ncurses/curses.h>
#endif

#include "mappa/Mappa.h"
#include "../model/pc/Character.hpp"
#include "../model/pc/inventory.h"

class View{
    protected:
        WINDOW * nameAndStats;
        WINDOW * outputMap;
        WINDOW * narrative;
        WINDOW * winventory;
    public:
        View();
        void print_nameAndStats(p_char c);
        void print_outputMap(Map* CurLevel);
        void print_narrative(queue<char*>* narrative);
        void print_inventory(inventory pg_inventory, int status);
        void clearoutputMap();

};


#endif //VIEW_H
