#include "weapons.h"



weapons::weapons()
{
    //ctor
   Item();
   this->type=WEAPON;

}
weapons::weapons(int level, string names[]):Item(names,level){
    this->type=WEAPON;
}

weapons::~weapons()
{
    //dtor
}




