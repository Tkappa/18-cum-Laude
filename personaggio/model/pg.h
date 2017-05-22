#ifndef PG_H
#define PG_H

#include "ability.h"
#include "position.h"
#include "weapons.h"
#include "inventory.h"

using namespace std;

class pg
{
    public:
        pg(string name);
        virtual ~pg();
         //setta abilita ed equipaggiamento del personaggio;
        void setup_character(char f);

        void getinfo();
        //setta l'equipaggiamento del personaggio
        void setupInventory(weapons a);
        //elimina dall'eqipaggiamento un oggetto
        void modificaInv(string a);

private:
        char character;
        ability ab;
    //  position pos; //implementata da Igor
        inventory w;
        string name;

};

#include "pg.cpp"
#endif // PG_H
