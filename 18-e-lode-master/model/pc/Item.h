#ifndef ITEM_H
#define ITEM_H
#include<string>
#include<ctime>
#include<cstdlib>
#define ITEM 0
#define ARMOR 1
#define WEAPON 2


using namespace std;




class Item
{
    public:
        Item();
        Item(string n[],int level);
        virtual ~Item();

        static int random();
        void setName(string n);
        void setValue(int n);

        int getValue();
        string getName();
        int getType();
        string generateName(string n[]);

        //decide che tipo di oggetto generare
        static Item* randomItem(int level);


    protected:
        string name;
        int value;
        int type;
};

#endif // ITEM_H
