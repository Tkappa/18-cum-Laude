//
// Created by Stefano Andriolo on 11/04/17.
//

#include "character.h"
#include <iostream>
using namespace std;


character::character(int life, int strength, int intelligence) {
    this->life = life;
    this->strength = strength;
    this->intelligence = intelligence;
    alive = true;
}


/*
 * Metodo che fa combattere due personaggi, semplicemente sottrae la forza di uno alla vita dell'altro;
 * se la vita di uno dei due arriva a zero, questo viene contrassegnato come morto
 */
void character::attacca(character otherCharacter) {

    this->life -= otherCharacter.strength;
    otherCharacter.life -= this->strength;

    this->alive = this->life > 0;
    otherCharacter.alive = otherCharacter.life > 0;
}


/*
 * Metodo che fa muovere il personaggio, implementazione da completare passando il parametro Stanza (o mappa
 * a seconda di come Igot decide di fare) e ritorna un booleano che indica se lo spostamento è avvenuto
 */
bool character::muovi(int direction) {

    // origine in alto a sinistra

    // variabili che conterranno, se sono state effettuate operazioni valide, la nuova posizione del personaggio
    int newX = this->xPos;
    int newY = this->yPos;

    switch (direction) {
        case 1:     // sinistra
            newX--;
            break;
        case 2:     // alto
            newY--;
            break;
        case 3:     // destra
            newX++;
            break;
        case 4:     // basso
            newY++;
            break;
        default:
            cout << "Direzione non valida" << endl;
            return false;
    }

    // if (Mappa.canMove(xPos, yPos, newX, newY)) {
}


void character::setXPos(int newX) {
    this->xPos = newX;
}


void character::setYPos(int newY) {
    this-yPos = newY;
}


bool character::isAlive() {
    return alive;
}


int character::getXPos() {
    return xPos;
}


int character::getYPos() {
    return yPos;
}


int character::getLife() {
    return life;
}


int character::getStrength() {
    return strength;
}


int character::getIntelligence() {
    return intelligence;
}

































