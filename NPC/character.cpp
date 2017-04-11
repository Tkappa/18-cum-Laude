//
// Created by Stefano Andriolo on 11/04/17.
//

#include "character.h"

#include <iostream>
#include <cmath>
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
    pos newPos = this->currentPosition;

    switch (direction) {
        case 1:     // sinistra
            newPos->xPos--;
            break;
        case 2:     // alto
            newPos->yPos--;
            break;
        case 3:     // destra
            newPos->xPos++;
            break;
        case 4:     // basso
            newPos->yPos++;
            break;
        default:
            cout << "Direzione non valida" << endl;
            return false;
    }

    // if (Mappa.canMove(xPos, yPos, newX, newY)) {
}


void character::setPos(pos newPosition) {
    this->currentPosition = newPosition;
}


bool character::isAlive() {
    return alive;
}


pos character::getPos() {
    return currentPosition;
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


int character::muoviVersoPersonaggio(character otherCharacter) {

    // differenza tra le componenti x ed y dei due personaggi
    int dx = abs(this->currentPosition.xPos - character->currentPosition.xPos);
    int dy = abs(this->currentPosition.yPos - character->currentPosition.yPos);

    // asse su sui muoversi, a seconda di quale dove esiste la distanza maggiore
    bool moveOnXAxis = dx > dy;

    if (moveOnXAxis) {  // considero l'asse x
        if (this->currentPosition.xPos > otherCharacter->currentPosition.xPos) { // se il personaggio corrente è più a destra
            return 1;   // vado a sinistra
        } else {
            return 3;   // altrimenti vado a destra
        }
    } else {
        if (this->currentPosition.yPos > otherCharacter->currentPosition.yPos) { // se il personaggio corrente è più in basso
            return 2;   // mi muovo verso l'alto
        } else {
            return 4;   // mi muovo verso il basso
        }
    }
}
