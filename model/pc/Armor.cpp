#include "Armor.h"
#include <iostream>

Armor::Armor(){
    Item();
    this->type=ARMOR;
}
Armor::Armor(int level, string names[]):Item(names,level){
    this->type=ARMOR;
   // std::cout << this->name << "----\n";
}


Armor::~Armor()
{
    //dtor
}
