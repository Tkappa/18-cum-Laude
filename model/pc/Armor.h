#ifndef ARMOR_H
#define ARMOR_H
#include<string>
#include<ctime>
#include<cstdlib>
#include "Item.h"

class Armor: public Item {

    public:
        Armor();
        Armor(int level, string names[]);
        virtual ~Armor();


    protected:
        //string names[7]={"a","b","c","d","e","f","g"};


   // private:
};

#endif // ARMOR_H
