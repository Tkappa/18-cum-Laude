/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Character.hpp
 * Author: Master
 *
 * Created on 13 maggio 2017, 12.12
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../../environment.hpp"
#include "ability.h"
#include "inventory.hpp"
#include "../../View/Mappa/Stanza.h"

using namespace std;



class Character {
    public:

    Character();
    Character(string n, ability s);
    Character(string n, ability s, Pos p);

    //Stabilisce in che direzione si deve muovere per raggiungere otherChar
    int moveToChar(Character * otherChar, Room room);

    //Controlla se muovendosi in quella direzione la sua posizione sarà la stessa di x
    bool willCollide(Character * x,int d);

    //Setter e getter di tutti i valori
    Pos getPos();
    virtual void setPos(Pos newPos);

    bool isAlive();
    void setAlive(bool isalive);

    void setStats(ability & s);
    ability getBaseStats();

    ability getFullStats();
    void setFullStats(ability & s);

    void setName(string s);
    string getName();

    string getSym();
    void setSym(string sym);

    void addMoney(int amount);
    int getMoney();
    void setMoney(int i);

    p_item getCurWeapon();
    void setCurWeapon(p_item weapon);
    p_item equipWeapon(p_item weapon);

    p_item getCurArmor();
    void setCurArmor(p_item weapon);
    p_item equipArmor(p_item weapon);


    inventory getInventory();


    //Valori che davano problemi se usati con il getter
    Pos pos;
    inventory pg_inventory;
protected:

    int money;
    string name;
    ability basestats;
    ability fullstats;
    p_item curWeapon;
    p_item curArmor;
    string sym;
    bool alive;
};

#endif /* CHARACTER_HPP */

