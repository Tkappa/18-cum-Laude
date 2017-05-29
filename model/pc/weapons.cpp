#include "weapons.h"



weapons::weapons()
{
    //ctor
    this->weap=weap_name();
    this->value=random();
}

weapons::~weapons()
{
    //dtor
}
string weapons:: weap_name(){
    string weap[5]={"spada"," arco ","scudo ","armatura "," cultura "};
    string agg[5]={"di Fuoco","aaa","bbb", "ccc","ddd"};
    int i=0;
    string name;
    i=random();
    name=weap[i];
    i=random();
    name= name+agg[i];

    return name;
}
string weapons::getName(){
    return this->weap;
}

int weapons ::getValue(){
    return this->value;
}

int weapons::random(){
    int n;
    n=(rand()%5);
    return n;
}

