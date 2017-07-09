
#ifndef INVENTORY_H
#define INVENTORY_H


#include "Item.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <list>

using namespace std;

typedef Item* p_item;
class inventory {
public:

    //crea una lista di armi

    list<p_item> listw;
    list<p_item> getInventory();
    //aggiunge un arma all'equipaggiamento del personaggio
    bool addItem(p_item a);
    //rimuove l'arma corrispondente ad un intero dato in input dall'inventario
    void deleteItem(string c);

    //converte in stringa l'inventario
    string inventoryToStr();



};

#endif// INVENTORY_H
