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
#include "weapons.h"
using namespace std;

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
    ability getStats();
    void setStats(ability & s);
    list<Item> getObject();
    string getName();
    string getDesc();
    void setDesc(string s);
    string getSym();
    void setSym(string sym);
    virtual string toStr();

    Pos pos;
protected:
    string name;
    string desc;
    ability stats;
    list<Item> object;
    string sym;
    bool alive;
};

#endif /* CHARACTER_HPP */

