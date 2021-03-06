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

#include "Character.hpp"

typedef Character* p_char;

using namespace std;

Character::Character() {

    this->pos = {0, 0, 0, 0};
    this->alive = true;
    this->money=0;
    this->fullstats=basestats;
    inventory pg_inventory();
}

Character::Character(string n, ability s) {
    this->name = n;
    this->basestats = s;
    this->alive = true;
    this->pos = {0, 0, 0, 0};
}

Character::Character(string n, ability s, Pos p) : Character(n, s) {
    this->pos = p;
}

void Character::setAlive(bool isalive){
    alive=isalive;
}

bool Character::isAlive() {
    return alive;
}

void Character::setMoney(int i){
    money=i;
}

int Character::getMoney(){
    return money;
}

void Character::addMoney(int amount){
    money+=amount;
}

void Character::setCurWeapon(p_item weapon){
    curWeapon=weapon;
}

p_item Character::getCurWeapon(){
    return curWeapon;
}

p_item Character::equipWeapon(p_item weapon){

    p_item temp=curWeapon;
    curWeapon=weapon;

    //Aggiorna le statistiche con i nuovi valori dell'arma
    fullstats.setStrength(basestats.getStrength()+curWeapon->getValue());

    //Ritorna l'arma vecchia
    return temp;
    }

p_item Character::getCurArmor(){
    return curArmor;
}

void Character::setCurArmor(p_item armor){
    curArmor=armor;
}

p_item Character::equipArmor(p_item armor){

    p_item temp=curArmor;
    curArmor=armor;
    //Aggiorna le statistiche con i nuovi valori dell'armatura
    fullstats.setDefense(basestats.getDefense()+curArmor->getValue());
    //Ritorna quella vecchia
    return temp;
}

inventory Character::getInventory(){
return pg_inventory;
}

void Character::setStats(ability & s) {
    basestats.setDefense(s.getDefense());
    basestats.setStrength(s.getStrength());
    basestats.setLife(s.getLife());
}

ability Character::getBaseStats() {
    return basestats;
}

void Character::setFullStats(ability & s){
    fullstats.setDefense(s.getDefense());
    fullstats.setStrength(s.getStrength());
    fullstats.setLife(s.getLife());
 }

ability Character::getFullStats() {
    return fullstats;
}

Pos Character::getPos() {
    return pos;
}

void Character::setPos(Pos newPos) {
    this->pos = newPos;
}

string Character::getName() {
    return name;
}

void Character::setName(string s){
    name=s;
}

string Character::getSym() {
    return sym;
}

void Character::setSym(string sym) {
    this->sym = sym;
}

int Character::moveToChar(Character *otherChar, Room room) {

    // ----------------------------------------------------------
    // ----------- LE POSIZIONI X ED Y SONO INVERTITE -----------
    // ----------------------------------------------------------

//    srand((uint) time(nullptr));

    // stanze in cui si trovano il personaggio principale e l'NPC corrente
//    Room otherCharRoom = map.getRoomForCoord(otherChar.pos.mapX, otherChar.pos.mapY);

    // (dx_room < 0) => stanza dell'altro personaggio a destra rispetto a questa
    int dx_room = this->pos.mapX - otherChar->pos.mapX;
    // (dy_room < 0) => stanza dell'altro personaggio sotto a questa
    int dy_room = this->pos.mapY - otherChar->pos.mapY;

    Pos sourcePos = this->pos, targetPos;

    if (dx_room != 0 || dy_room != 0) {
        // stanze diverse

        // ------ se i due personaggi sono distanti al massimo 1 stanza ------
        bool oneRoomNearX = abs(dx_room) == 1;
        bool oneRoomNearY = abs(dy_room) == 1;

        // se sono più distanti di una stanza sia sull'asse x che y ritorno una direzione a caso
        if ((!oneRoomNearX && !oneRoomNearY) || (oneRoomNearX && oneRoomNearY))
            return rand() % 4 + 1;

        // se sono nelle stanze una di fianco all'altra sull'asse x
        if (oneRoomNearX) {
            int direction = dx_room < 0 ? 4 : 2;    // 4 = giù; 2 = su
            bool hasDoorInDirection = room.hasDoor(direction);

            if (hasDoorInDirection) {
                int targetPosX = direction == 4 ? roomHeight : 0;
                targetPos = { 0, 0, targetPosX, roomLenght / 2 };
            }

        } else {    // oneRoomNearY == true, una stanza sopra l'altra sull'asse y
            int direction = dy_room < 0 ? 3 : 1;    // 3 = destra; 1 = sinistra
            bool hasDoorInDirection = room.hasDoor(direction);

            if (hasDoorInDirection) {
                int targetPosY = direction == 3 ? roomLenght : 0;
                targetPos = { 0, 0, roomHeight / 2, targetPosY };
            }
        }

        // decido se muovermi sull'asse verticale o orizzonatale, anche a seconda della presenza di porte
        // mi muovo nella direzione della porta
    } else {
        targetPos = otherChar->pos;
    }

    // stessa stanza, o stanze diverse ma considero la porta come destinazione verso cui muoversi

    // differenza tra le componenti x ed y delle due posizioni
    int dx = abs(sourcePos.stanzX - targetPos.stanzX);
    int dy = abs(sourcePos.stanzY - targetPos.stanzY);

    // asse su cui muoversi, a seconda di quale dove esiste la distanza maggiore
    bool moveOnXAxis = dx > dy;

    if (moveOnXAxis) { // considero l'asse x
        if (sourcePos.stanzX < targetPos.stanzX) { // se il personaggio corrente è più in alto
            return 4; // vado in giù
        } else {
            return 2; // altrimenti vado in su
        }
    } else {
        if (sourcePos.stanzY < targetPos.stanzY) { // se il personaggio corrente è più a sinistra
            return 3; // mi muovo verso destra
        } else {
            return 1; // mi muovo verso sinistra
        }
    }
}


bool Character::willCollide(Character * x,int d){
    int xaxis=0,yaxis=0;
    //Prende la direzione e modifica l'asse di controllo corrispondente
    switch(d){
        case Direction::left:
            yaxis= -1;
        break;

        case Direction::right:
            yaxis= 1;
        break;

        case Direction::up:
            xaxis= -1;
        break;

        case Direction::down:
            xaxis=1;
        break;
        default:
        break;
        }

    //Controlla se il personaggio che si sta controllando e' in quella direzione rispetto al personaggio principale
    if(pos.mapX==x->getPos().mapX && pos.mapY==x->getPos().mapY && (pos.stanzX+xaxis)==x->getPos().stanzX && (pos.stanzY+yaxis)==x->getPos().stanzY )
        return true;
    return false;
}
