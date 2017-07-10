#include "inventory.h"

inventory::inventory(){
    list<p_item> listw;
}

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
return listw;
}

p_item inventory:: deleteItem(string id) {
    int offset = 0;
    bool found=false;
    bool ciclodopofound=false;
    p_item temp=nullptr;
   for(list<Item* >::iterator i=listw.begin(); i!=listw.end();++i){
        if(found) ciclodopofound=true;
        cout<<endl<<"sto controllando: "<<(*i)->getName()<<endl;
        string tempId=(*i)->getInventoryId();
        cout<<tempId<<"<- attuale , quello che cerco ->"<<id<<endl;
        if( id == tempId){
            cout<<"L'ho trovato e lo sto per cancellare"<<endl;
            temp=*i;
            this->listw.erase(i);
            offset=-1;
            found=true;
            cout<<"Cancellato e messo find a true"<<endl;
        }
        else if(ciclodopofound){
        tempId[0]+=offset;
        cout<<"Sto per cambiare l'id a "<<(*i)->getName()<<" NuovoId:"<<tempId<<endl;

        (*i)->setInventoryId(tempId);
        }
   }
   cout<<"sto per fare il return di: "<<temp->getName();
   return temp;
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





