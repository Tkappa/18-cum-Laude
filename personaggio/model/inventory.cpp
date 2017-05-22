#include "inventory.h"




void inventory:: addWeapons(weapons a){
    this->listw.push_back(a);

}
/*
void inventory:: deleteWeapons(string a) {                  //non corretta
   for(list<weapons>::iterator i=listw.begin(); i!=listw.end();++i){
        if((*i).getName()==a)
            listw.remove(i);
}
*/
void inventory:: printWeapons() {
    for(list<weapons>::iterator i=listw.begin(); i!=listw.end();++i)
            cout<<"arma: "<<(*i).getName()<<endl;
}
