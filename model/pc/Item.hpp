#ifndef ITEM_H
#define ITEM_H

#include "../../environment.hpp"

using namespace std;

class Item
{
    public:
        //Costruttore a vuoto
        Item();
        //Costruttore randomico
        Item(int level,mapPos position);
        //Costruttore a mano
        Item(string name, int value,int type);
        virtual ~Item();

        //Setter e getter
        void setName(string n);
        string getName();

        void setValue(int n);
        int getValue();

        void setSym(string c);
        string getSym();

        void setInventoryId(string c);
        string getInventoryId();

        void setPos(mapPos x);

        int getPrice();

        int getType();

        //Sceglie un nome casuali dall'array passato per parametro
        string generateName(string n[],int x);



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
