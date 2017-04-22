
#ifndef INVENTORY_H
#define INVENTORY_H


#include "weapons.h"
#include <iostream>

using namespace std;


class inventory {
public:

    //crea una lista di armi
    list<weapons> listw;

    //aggiunge un arma all'equipaggiamento del personaggio
    void addWeapons(weapons a);
    //rimuove un arma dall'equipaggiamento //(decidere il motivo per il quale rimuoverla [ scelta del personaggio o evento])
    void deleteWeapons(string a);


    void printWeapons();



};

#include "inventory.cpp"

#endif// INVENTORY_H
