
#include "ability.h"


using namespace std;

ability::ability() {
    this->defense = 1;
    this->strength = 1;
    this->life = 1;
}

void ability::setDefense(int n) {
    this->defense = n;
}

void ability::setStrength(int n) {
    this->strength = n;
}

void ability::setLife(int n) {
    this->life = n;
}

int ability::getDefense() {
    return defense;
}

int ability::getStrength() {
    return strength;
}

int ability::getLife() {
    return life;
}
