#include "Item.h"
#include "environment.hpp"
#include <iostream>

using namespace std;

Item::Item()
{
    this->name="";
    this->value=0;
    this->type=ITEM;
}


Item::Item(int level,mapPos i_pos){
    string weapons[7]={"g","h","i","l","m","n","o"};
    string armors[7]={"a","b","c","d","e","f","g"};
    int i;
    i=random()%4;
    Item* a;
    if(i==0){
        name=generateName(weapons);//genero un'arma
        value=level+(random()%3);
        type=WEAPON;
        symb="w";
    }
    if(i==1){
        name=generateName(armors);//genero un armatura
        value=level+(random()%3);
        type=ARMOR;
        symb="a";
    }
    if(i==2){
        name="money";
        value=(1+level)*((random()%20)+1);
        type=MONEY;
        symb="$";
    }
    if(i==3){
        string temp="Pozione di cura ";

        int poz=level/3+random()%10;
        if (poz<6){
            value=5;
            temp+="piccola";
        }
        else if (poz<11){
            value=10;
            temp+="media";
        }
        else {
            value=15;
            temp+="grande";
        }

        name=temp;
        type=POTION;
        symb="p";
    }
    position=i_pos;

}
Item::Item(int level){
    string weapons[7]={"g","h","i","l","m","n","o"};
    string armors[7]={"a","b","c","d","e","f","g"};
    int i;
    i=random()%2;
    Item* a;
    if(i==0){
        name=generateName(weapons);//genero un'arma
        value=level+(random()%3);
        type=WEAPON;
    }
    if(i==1){
        name=generateName(weapons);//genero un'arma
        value=level+(random()%3);
        type=WEAPON;
    }


}

Item::Item( string name, int value,int type){
    this->name=name;
    this->value=value;
    this->type=type;
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




void Item::setSym(string c){
    symb=c;
}
void Item::setInventoryId(string c){
    inventoryId=c;
}
string Item::getSym(){
        return symb;
        }
string Item::getInventoryId(){
        return inventoryId;
        }
Item::~Item()
{
    //dtor
}
