#include <functional>
#include <string>
#include "majorCharacter.h"
#include "aiutante.h"

using namespace std;

// TODO: Risolvere il problema del nome e della descrizione, quando vengono passati al costruttori non vengono assegnati

majorCharacter::majorCharacter(string name, string description, STATS params) : character(params) {
    this->name = name;
    this->description = description;

    follower = NULL;
}


majorCharacter::majorCharacter(string name, string description, STATS params, POS position) : majorCharacter(name, description, params) {
    this->currentPosition = position;
}


majorCharacter::majorCharacter(string name, string description, STATS params, POS position, aiutante * follower) : majorCharacter(name, description, params, position) {

    setFollower(follower);
}


void majorCharacter::setFollower(aiutante * follower) {
    this->follower = follower;
}


void majorCharacter::setPos(POS newPos) {

    if (this->follower != NULL) {   // se è presente un aiutante per il personaggio corrente
        // imposto la posizione dell'aiutante uguale a quella del personaggio corrente
        follower->setPos((POS) {this->currentPosition.xPos, this->currentPosition.yPos});
    }

    // aggiorno la posizione del personaggio corrente
    this->currentPosition = newPos;
}


string majorCharacter::toString() {
    string s = "MajorCharacter - life: ";
    s += to_string(this->statistics.life);
    s += ", strength: ";
    s += to_string(this->statistics.strength);
    s += ", intelligence: ";
    s += to_string(this->statistics.intelligence);
    s += ", xPos: ";
    s += to_string(this->currentPosition.xPos);
    s += ", yPos: ";
    s += to_string(this->currentPosition.yPos);
    s += this->isAlive() ? ", ALIVE, nome: " : ", DEAD, nome: ";
    s += this->getName();
    s += ", aiutante: [";
    s += this->follower != NULL ? this->follower->toString() : "NULL";
    s += "]";

    return s;
}


string majorCharacter::getName() {
    return this->name;
}


string majorCharacter::getDescription() {
    return this->description;
}
