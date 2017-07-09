
#ifndef VIEW_H
#define VIEW_H

#include <ncurses/curses.h>
#include "mappa/Mappa.h"
#include "../model/pc/Character.hpp"
#include "../model/pc/inventory.h"

class View{
    protected:
        WINDOW * nameAndStats;
        WINDOW * outputMap;
        WINDOW * narrative;
        WINDOW * winventory;
        WINDOW * death;
        WINDOW * exitconfirmation;
    public:
        View();
        void print_exitconfirmation();
        void print_death(p_char pgprincipale ,p_char omicida=nullptr);
        void print_nameAndStats(p_char c);
        void print_outputMap(Map* CurLevel);
        void print_narrative(queue<char*>* narrative);
        void print_inventory(inventory pg_inventory, int status);
        void clearoutputMap();

};


#endif //VIEW_H
