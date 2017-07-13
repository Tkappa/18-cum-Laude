#include "inventory.hpp"

inventory::inventory(){
    list<p_item> listw;
}

bool inventory:: addItem(p_item a){

    if(listw.size()<8){
        string temp="a";

        //97 e' la lettera a da dove partono gli ID dell'inventario
        temp[0]=97+listw.size();
        a->setInventoryId(temp);
        listw.push_back(a);
        return true;
    }
    return false;

}

p_item inventory::getByID(string id){

    for(std::list<p_item>::iterator i=listw.begin(); i!=listw.end();++i){
        if((*i)->getInventoryId()==id){
            p_item temp=*i;
            return temp;
        }
    }
    return nullptr;
}

list<p_item> inventory::getInventory(){
    return listw;
}

p_item inventory:: deleteItem(string id) {

    int offset=1;
    p_item temp=nullptr;

    std::list<p_item>:: iterator eliminatore;
    std::list<p_item>:: iterator i=listw.begin();
    bool trovato=false;

    while(i!=listw.end()){

        string controllo=(*i)->getInventoryId();

        if(trovato){
            //Se ha eliminato l'oggetto tutti i valori dopo devono slittare indietro di una lettere
            controllo[0]-=offset;
            (*i)->setInventoryId(controllo);
        }
        if((controllo==id)&&!trovato){
            //Se la lettera e' uguale e non ha gia trovato l'oggetto lo elimina dalla lista
            temp=*i;
            eliminatore=i++;
            listw.erase(eliminatore);
            trovato=true;
        }
        else{
            ++i;
        }
    }
    //Ritorna l'oggetto eliminato o null in caso non sia stato trovato
    return temp;
}

int inventory::getSize(){
    return listw.size();
}



