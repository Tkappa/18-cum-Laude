#include "inventory.h"



void inventory:: addItem(Item a){
    if(listw.size()<10)
        this->listw.push_back(a);

}

void inventory:: deleteItem(int a) {
    int c = 0;
    bool find=0;

   for(list<Item>::iterator i=listw.begin(); i!=listw.end() && find==0;++i){
        if( c == a){
            this->listw.erase(i);
            find=1;
        }
        else{
            c++;
        }
   }

}

string inventory:: inventoryToStr() {
    char buf[10];
    string s="",tmp="";
    int count=0;
    for(list<Item>::iterator i=listw.begin(); i!=listw.end();++i){

        tmp = "Item name: " + (*i).getName() + " - value: ";
        sprintf(buf, "%d", (*i).getValue());
        s += buf;
        tmp += " - type: ";
        sprintf(buf, "%d", (*i).getType());
        tmp+= buf;
        tmp+= "- id: ";
        sprintf(buf, "%d", count);
        tmp += buf;
        tmp += "\n";

        s=s+tmp;
        count++;
    }

    return s;
}





