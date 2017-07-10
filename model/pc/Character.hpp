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

#include <string>
#include <list>
#include "environment.hpp"
#include "ability.h"
#include "inventory.hpp"
using namespace std;

typedef Item* p_item;
class Character {
public:
    Character();
    Character(string n, ability s);
    Character(string n, ability s, Pos p);
    Character(string n, ability s, Pos p, string d);
    bool move(int direction);
    int moveToChar(Character & otherChar);
    bool attack(Character & otherChar);
    Pos getPos();
    virtual void setPos(Pos newPos);
    bool isAlive();
    ability getBaseStats();
    ability getFullStats();
    void setStats(ability & s);
    void setName(string s);
    void setFullStats(ability & s);
    string getName();
    string getDesc();
    void setDesc(string s);
    string getSym();
    void setSym(string sym);
    virtual string toStr();

    void addMoney(int amount);

    p_item getCurWeapon();
    void setCurWeapon(p_item weapon);
    p_item equipWeapon(p_item weapon);

    p_item getCurArmor();
    void setCurArmor(p_item weapon);
    p_item equipArmor(p_item weapon);
    int getMoney();

    void setMoney(int i);
    Pos pos;
    inventory getInventory();
    inventory pg_inventory;
protected:

    int money;
    string name;
    string desc;
    ability basestats;
    ability fullstats;
    p_item curWeapon;
    p_item curArmor;
    string sym;
    bool alive;
};

#endif /* CHARACTER_HPP */

