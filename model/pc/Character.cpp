/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Character.cpp
 * Author: Master
 *
 * Created on 13 maggio 2017, 12.12
 */
#include <iostream>
#include <cstdlib>
#include "ability.h"
#include <cstdio>
#include "Character.hpp"

using namespace std;

Character::Character() {
    this->name = "Flaffy";
    this->basestats;
    //this->stats = {5, 5, 5};
    this->pos = {0, 0, 0, 0};
    //Item w;
    //this->object.push_back(w);
    this->desc = "Descrizione di prova";
    this->money=0;
    this->fullstats=basestats;
}
p_item Character::getCurWeapon(){
return curWeapon;
}

void Character::setMoney(int i){
money=i;}
void Character::setCurWeapon(p_item weapon){
curWeapon=weapon;
}

p_item Character::equipWeapon(p_item weapon){
    p_item temp=curWeapon;
    curWeapon=weapon;
    fullstats.setStrength(basestats.getStrength()+curWeapon->getValue());
    return temp;
    }

p_item Character::getCurArmor(){
return curArmor;
}

void Character::setCurArmor(p_item armor){
curArmor=armor;}

int Character::getMoney(){
return money;}

p_item Character::equipArmor(p_item armor){
p_item temp=curArmor;
    curArmor=armor;
    fullstats.setDefense(basestats.getDefense()+curArmor->getValue());
    return temp;}

inventory Character::getInventory(){
return pg_inventory;
}

Character::Character(string n, ability s) {
    this->name = n;
    this->basestats = s;
    this->alive = true;
    this->pos = {0, 0, 0, 0};
    //Item w;
    //this->object.push_back(w);
    this->desc = "Descrizione di prova";
}

Character::Character(string n, ability s, Pos p) : Character(n, s) {
    this->pos = p;
}

Character::Character(string n, ability s, Pos p, string d) : Character(n, s, p) {
    desc = d;
}

void Character::addMoney(int amount){
money+=amount;
}
bool Character::move(int direction) {
    // origine in alto a sinistra
    // variabili che conterranno, se sono state effettuate operazioni valide, la nuova posizione del personaggio
    Pos newPos = this->pos;

    switch (direction) {
        case 1: // sinistra
            newPos.stanzX--;
            break;
        case 2: // alto
            newPos.stanzY--;
            break;
        case 3: // destra
            newPos.stanzX++;
            break;
        case 4: // basso
            newPos.stanzY++;
            break;
        default:
            cout << "Direzione non valida" << endl;
            return false;
    }

    // if (Mappa.canMove(xPos, yPos, newX, newY)) {
    return false;
}

int Character::moveToChar(Character & otherChar) {
    // differenza tra le componenti x ed y dei due personaggi
    int dx = abs(this->pos.stanzX - otherChar.pos.stanzX);
    int dy = abs(this->pos.stanzY - otherChar.pos.stanzY);

    // asse su cui muoversi, a seconda di quale dove esiste la distanza maggiore
    bool moveOnXAxis = dx > dy;

    if (moveOnXAxis) { // considero l'asse x
        if (this->pos.stanzX > otherChar.pos.stanzX) { // se il personaggio corrente è più a destra
            return 1; // vado a sinistra
        } else {
            return 3; // altrimenti vado a destra
        }
    } else {
        if (this->pos.stanzY > otherChar.pos.stanzY) { // se il personaggio corrente è più in basso
            return 2; // mi muovo verso l'alto
        } else {
            return 4; // mi muovo verso il basso
        }
    }
}

void Character::setStats(ability & s) {
    basestats.setDefense(s.getDefense());
    basestats.setStrength(s.getStrength());
    basestats.setLife(s.getLife());
}
 void Character::setFullStats(ability & s){
    fullstats.setDefense(s.getDefense());
    fullstats.setStrength(s.getStrength());
    fullstats.setLife(s.getLife());
 }

bool Character::attack(Character & otherChar) {
    bool ok = false;
    //    if (otherChar == NULL) ok = false;
    //    else {
    ability temp = this->getBaseStats();
    cout << temp.getLife();
#ifdef DEBUG
#endif
    temp.setLife(temp.getLife() - otherChar.getBaseStats().getStrength());
    this->setStats(temp);
#ifdef DEBUG
    ability deb = this->getStats();
    cout << deb.toStr();
#endif
    this->alive = this->getBaseStats().getLife() > 0;

    temp = otherChar.getBaseStats();
    temp.setLife(temp.getLife() - this->getBaseStats().getStrength());
    //temp.seotherChar.getStats().getLife() -= this->getStats().getLife();
    otherChar.setStats(temp);
    otherChar.alive = otherChar.getBaseStats().getLife() > 0;
    //        ok = true;
    //    }
    return ok;
}

Pos Character::getPos() {
    return pos;
}

void Character::setPos(Pos newPos) {
    this->pos = newPos;
}

bool Character::isAlive() {
    return alive;
}

ability Character::getBaseStats() {
    return basestats;
}
ability Character::getFullStats() {
    return fullstats;
}



string Character::getName() {
    return name;
}

string Character::getDesc() {
    return desc;
}

void Character::setDesc(string s) {
    desc = s;
}

string Character::getSym() {
    return sym;
}

void Character::setSym(string sym) {
    this->sym = sym;
}

/*virtual*/ string Character::toStr() {
    char buf[5];
    //s += to_string(this->stats.life);
    string s = "Character " + this->name + " - life: ";
    sprintf(buf, "%d", this->basestats.getLife());
    s += buf;
    //s += to_string(this->stats.strength);
    s += ", strength: ";
    sprintf(buf, "%d", this->basestats.getStrength());
    s += buf;
    //s += to_string(this->stats.intelligence);
    s += ", intelligence: ";
//    sprintf(buf, "%d", this->basestats.getIntelligence());
    s += buf;
    //s += to_string(this->currentPos.x);
    s += ", x: ";
    sprintf(buf, "%d", this->pos.stanzX);
    s += buf;
    //s += to_string(this->currentPos.y);
    s += ", y: ";
    sprintf(buf, "%d", this->pos.stanzY);
    s += buf;
    s += this->isAlive() ? ", ALIVE" : ", DEAD";
    s += "\n";

    return s;
}

