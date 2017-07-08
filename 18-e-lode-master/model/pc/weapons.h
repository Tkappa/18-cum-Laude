#ifndef WEAPONS_H
#define WEAPONS_H

#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Item.h"

using namespace std;

class weapons: public Item
{
    public:
        weapons();
        weapons(int level, string names[]);
        virtual ~weapons();


protected:


};

#endif // WEAPONS_H
