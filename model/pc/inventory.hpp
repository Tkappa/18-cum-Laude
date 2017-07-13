
#ifndef INVENTORY_H
#define INVENTORY_H


#include "Item.hpp"

#include "../../enviroment.hpp"

using namespace std;

typedef Item* p_item;
class inventory {
public:

    //crea una lista di armi
    inventory();

    list<p_item> listw;

    //getter dell'inventario
    list<p_item> getInventory();

    //aggiunge un oggetto all'equipaggiamento del personaggio
    bool addItem(p_item a);

    //rimuove l'arma corrispondente ad un carattere dato in input dall'inventario
    p_item deleteItem(string c);

    //Ritorna un oggetto con ID corrispondente a quello passato in parametro
    p_item getByID(string id);

    int getSize();

};

#endif// INVENTORY_H
