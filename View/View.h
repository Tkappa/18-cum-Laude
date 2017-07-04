
#ifndef VIEW_H
#define VIEW_H

#include <ncurses/curses.h>
#include "mappa/Mappa.h"
#include "../model/pc/Character.hpp"
class View{
    protected:
        WINDOW * nameAndStats;
        WINDOW * outputMap;
        WINDOW * narrative;
        WINDOW * inventory;
    public:
        View();
        void print_nameAndStats(Character &c);
        void print_outputMap(Mappa* CurLevel);
        void print_narrative(queue<char*>* narrative);
        void print_inventory(string s);
        void clearoutputMap();

};


#endif //VIEW_H
