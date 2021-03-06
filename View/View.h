
#ifndef VIEW_H
#define VIEW_H

#ifdef __APPLE__ && __MACH__
    #include <ncurses.h>
#else
    #include <ncurses/curses.h>
#endif

#include "mappa/Mappa.h"
#include "../environment.hpp"
#include "../model/pc/Character.hpp"
#include "../model/pc/inventory.hpp"

class View{
    protected:
        WINDOW * nameAndStats;
        WINDOW * outputMap;
        WINDOW * narrative;
        WINDOW * winventory;
        WINDOW * death;
        WINDOW * exitconfirmation;
        WINDOW * introduction;
        WINDOW * classselection;
        WINDOW * victory;
        WINDOW * help;
    public:
        View();

        void print_help();
        void print_victory();
        void print_introduction();
        void print_exitconfirmation();
        void print_classselection();
        void print_death(p_char pgprincipale ,p_char omicida=nullptr);
        void print_nameAndStats(p_char c);
        void print_outputMap(Map* CurLevel);
        void print_narrative(queue<char*>* narrative);
        void print_inventory(inventory pg_inventory, int status);
        void clearoutputMap();
        void clearAndDestroy();

};


#endif //VIEW_H
