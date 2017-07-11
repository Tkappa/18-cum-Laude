#include "inventory.hpp"

inventory::inventory(){
    list<p_item> listw;
}

bool inventory:: addItem(p_item a){
    if(listw.size()<8){
        string temp="a";
        temp[0]=97+listw.size();
        //cout<<"aggiunto elemento di id: "<<temp<<" all'inventario"<<endl;
        a->setInventoryId(temp);
        listw.push_back(a);
        return true;}
    return false;

}
list<p_item> inventory::getInventory(){
return listw;
}

p_item inventory:: deleteItem(string id) {
    int offset=0;
    p_item temp=nullptr;
    std::list<p_item>:: iterator eliminatore;
    std::list<p_item>:: iterator i=listw.begin();
    bool trovato=false;



    while(i!=listw.end()){
        string controllo=(*i)->getInventoryId();
        if(trovato){
            controllo[0]+=offset;
            (*i)->setInventoryId(controllo);
        }
        if(controllo==id&&!trovato){
            temp=*i;
            eliminatore=i++;
            listw.erase(eliminatore);
            trovato=true;
        }
        else{
            ++i;
        }
//        cout<<"Indirizzo di i:"<<*i<<" Indirizzo di list.end() "<<listw.end()<<endl;
    }
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





