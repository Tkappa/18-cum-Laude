#include "Item.hpp"


using namespace std;

Item::Item(){
    this->name="";
    this->value=0;
    this->type=ITEM;
}

Item::Item(int level,mapPos i_pos){
    string weapons[13]={"Tutorial su Youtube","Libro Originale","Libro Fotocopiato","Blocco appunti nuovo","Penna di lusso","Domanda su Yahoo Answers","Borsa di studio","Tablet","Computer","Kindle","Telefono","Appunti","Ripetizioni"};
    string armors[8]={"Pass sala studio","Integratori al fosforo","Caffe normale","Caffe amaro","Caffe dello studente","Serata chiuso in casa","Appuntamento studio","Esame il giorno dopo"};
    string potions[9]={"Pausa facebook","Redbull","Incontro con amici","Meme ","Pausa TV","Videogioco nuovo","Weekend di vacanza","Weekend a casa","Un buon voto"};

    int i;
    int randitem=rand()%100;
    //Favorisce la creazione di soldi e pozioni rispetto a armi e armature
    if(randitem<50){
        i=2;
    }
    else if(randitem<70){
        i=3;

    }
    else{
        i=rand()%2;
    }

    Item* a;
    if(i==0){
        name=generateName(weapons,13);//genero un'arma
        value=2+level+(rand()%3);
        type=WEAPON;
        symb="w";
    }
    if(i==1){
        name=generateName(armors,8);//genero un armatura
        value=2+level+(rand()%3);
        type=ARMOR;
        symb="a";
    }
    if(i==2){
        name="money";
        value=(1+level)*((rand()%20)+1);
        type=MONEY;
        symb="$";
    }
    if(i==3){
        string temp=generateName(potions,9);

        //Stabilisce quanto potente e' la pozione
        int poz=level/3+rand()%10;

        if (poz<6){
            value=10;
            temp+=" minore";
        }
        else if (poz<11){
            value=20;
            temp+=" comune";
        }
        else {
            value=30;
            temp+=" maggiore";
        }

        name=temp;
        type=POTION;
        symb="p";
    }
    position=i_pos;

    //Stabilisce il prezzo dal negoziante
    price=value*12;

    if(type==3){
        //Se e' una pozione la fa costare leggermente meno
        price=value*7;
    }
}

Item::Item( string name, int value,int type){
    this->name=name;
    this->value=value;
    this->type=type;
}

void Item::setName(string n){
    this->name = n;
}

string Item::getName(){
    return this->name;
}

void Item::setValue(int n){
    this->value=n;
}

int Item:: getValue(){
    return value;
}

void Item::setSym(string c){
    symb=c;
}

string Item::getSym(){
    return symb;
}

void Item::setInventoryId(string c){
    inventoryId=c;
}

string Item::getInventoryId(){
    return inventoryId;
}

void Item::setPos(mapPos x){
    position=x;
}

string Item::generateName(string n[],int x){
    string str;
    int i=0;
    i=(rand()%x);
    str = n[i];
    return str;
}

int Item:: getType(){
    return type;
}

int Item::getPrice(){
    return price;
}



Item::~Item(){
    //dtor
}
