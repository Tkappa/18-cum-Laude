#include "inventory.hpp"



bool inventory:: addItem(p_item a){
    if(listw.size()<8){
        string temp="a";
        temp[0]=97+listw.size();
        //cout<<"aggiunto elemento di id: "<<temp<<" all'inventario"<<endl;
        a->setInventoryId(temp);
        this->listw.push_back(a);
        return true;}
    return false;

}
list<p_item> inventory::getInventory(){
return listw;}

void inventory:: deleteItem(string id) {
    int offset = 0;
    bool find=0;

   for(list<Item* >::iterator i=listw.begin(); i!=listw.end();++i){
        string tempId=(*i)->getInventoryId();
        if( id == tempId){
            this->listw.erase(i);
            offset=-1;
        }
        tempId[0]+=offset;
        (*i)->setInventoryId(tempId);
   }
}

string inventory:: inventoryToStr() {
    /*char buf[10];
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
*/}





