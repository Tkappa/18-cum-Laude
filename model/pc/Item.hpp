#ifndef ITEM_H
#define ITEM_H
#include<string>
#include<ctime>
#include<cstdlib>
#include "environment.hpp"

#define ITEM 0
#define ARMOR 2
#define WEAPON 1
#define MONEY 3
#define POTION 4


using namespace std;




class Item
{
    public:
        Item();
        Item(int level);
        Item(int level,mapPos position);
        Item(string name, int value,int type);
        virtual ~Item();

        static int random();
        void setName(string n);
        void setValue(int n);

        int getValue();
        string getName();
        int getType();
        string generateName(string n[]);
        void setSym(string c);
        string getSym();
        void setInventoryId(string c);
        string getInventoryId();
        void setPos(mapPos x);
        int getPrice();

        //decide che tipo di oggetto generare
        static Item* randomItem(int level);

        mapPos position;

    protected:
        string name;
        int value;
        int type;
        int price;
        string symb;
        string inventoryId;
};

#endif // ITEM_H
