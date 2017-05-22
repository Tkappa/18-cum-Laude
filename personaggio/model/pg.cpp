#include "pg.h"
#include <string>
//#include "ability.h"


pg::pg(string name1){
    this->name=name1;
    this->character='@';

}

void pg:: setup_character(char f){

    switch(f) {
        case 'a':
            this->ab.setIntelligence(ab.random());
            this->ab.setStrength(ab.random());
            break;
        case 'b':
            this->ab.setIntelligence(ab.random());
            this->ab.setStrength(ab.random());
            break;
        case 'c':
            this->ab.setIntelligence(ab.random());
            this->ab.setStrength(ab.random());
            break;
        case 'd':
            this->ab.setIntelligence(ab.random());
            this->ab.setStrength(ab.random());
            break;
        default:
            cout<<"Error! Insert a letter between a-b-c-d";
            break;
    }
}

void pg::setupInventory(weapons a) {
    this->w.addWeapons(a);
}
//void pg::modificaInv(weapons a){///****DA IMPLEMENTARE*****///
//    this->w.deleteWeapons(a);
//}

void pg:: getinfo(){
    cout<<this->name<<endl;
    cout<<"intelligence: "<<this->ab.getIntelligence()<<" strength: "<<this->ab.getStrength()<<" Life: "<<this->ab.getLife()<<endl;
    this->w.printWeapons();
}

pg::~pg()
{
    //dtor
}
