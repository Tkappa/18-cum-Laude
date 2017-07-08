#include "Item.h"
#include "weapons.h"
#include "Armor.h"
#include <iostream>

using namespace std;

Item::Item()
{
    this->name="";
    this->value=0;
    this->type=ITEM;
}

Item::Item( string n[7], int level){
    setName(generateName(n));
    this->value=level+random();
    this->type=ITEM;
}

void Item::setName(string n){

    this->name = n;
}

void Item::setValue(int n){
    this->value=n;
}

int Item:: getType(){
    return type;
}

string Item::getName(){
    return this->name;
}
int Item:: getValue(){
    return value;
}

string Item::generateName(string n[]){
    string str;
    int i=0;
    i=(random()%7);
    str = n[i];
    return str;
}

int Item::random(){
    int n;
    n=(rand()%5);
    return n;
}

Item* Item::randomItem(int level){
    int i;
    i=random()%2;
    Item* a;
    if(i==0){
        string names[7]={"g","h","i","l","m","n","o"};//genero un'arma
        a= new weapons(level,names);
    }
    if(i==1){
        string names[7]={"a","b","c","d","e","f","g"};
        a = new Armor(level, names);
    }

return a;

}

Item::~Item()
{
    //dtor
}
