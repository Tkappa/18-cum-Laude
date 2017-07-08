
#ifndef INVENTORY_H
#define INVENTORY_H


#include "Item.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <list>

using namespace std;


class inventory {
public:

    //crea una lista di armi

    list<Item> listw;

    //aggiunge un arma all'equipaggiamento del personaggio
    void addItem(Item a);
    //rimuove l'arma corrispondente ad un intero dato in input dall'inventario
    void deleteItem(int a);

    //converte in stringa l'inventario
    string inventoryToStr();



};

#endif// INVENTORY_H
