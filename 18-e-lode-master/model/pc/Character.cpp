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
    this->stats;
    //this->stats = {5, 5, 5};
    this->pos = {0, 0, 0, 0};
    Item w;
    this->object.push_back(w);
    this->desc = "Descrizione di prova";
}

Character::Character(string n, ability s) {
    this->name = n;
    this->stats = s;
    this->alive = true;
    this->pos = {0, 0, 0, 0};
    Item w;
    this->object.push_back(w);
    this->desc = "Descrizione di prova";
}

Character::Character(string n, ability s, Pos p) : Character(n, s) {
    this->pos = p;
}

Character::Character(string n, ability s, Pos p, string d) : Character(n, s, p) {
    desc = d;
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
    stats.setIntelligence(s.getIntelligence());
    stats.setStrength(s.getStrength());
    stats.setLife(s.getLife());
}

bool Character::attack(Character & otherChar) {
    bool ok = false;
    //    if (otherChar == NULL) ok = false;
    //    else {
    ability temp = this->getStats();
    cout << temp.getLife();
#ifdef DEBUG
#endif
    temp.setLife(temp.getLife() - otherChar.getStats().getStrength());
    this->setStats(temp);
#ifdef DEBUG
    ability deb = this->getStats();
    cout << deb.toStr();
#endif
    this->alive = this->getStats().getLife() > 0;

    temp = otherChar.getStats();
    temp.setLife(temp.getLife() - this->getStats().getStrength());
    //temp.seotherChar.getStats().getLife() -= this->getStats().getLife();
    otherChar.setStats(temp);
    otherChar.alive = otherChar.getStats().getLife() > 0;
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

ability Character::getStats() {
    return stats;
}

list<Item> Character::getObject() {
    return object;
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
    sprintf(buf, "%d", this->stats.getLife());
    s += buf;
    //s += to_string(this->stats.strength);
    s += ", strength: ";
    sprintf(buf, "%d", this->stats.getStrength());
    s += buf;
    //s += to_string(this->stats.intelligence);
    s += ", intelligence: ";
    sprintf(buf, "%d", this->stats.getIntelligence());
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

