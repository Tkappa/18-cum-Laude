
#include "ability.h"
#include <string>
#include <stdio.h>

using namespace std;

ability::ability() {
    this->intelligence = 5;
    this->strength = 5;
    this->life = 10;
}

void ability::setIntelligence(int n) {
    this->intelligence = n;
}

void ability::setStrength(int n) {
    this->strength = n;
}

void ability::setLife(int n) {
    this->life = n;
}

int ability::getIntelligence() {
    return intelligence;
}

int ability::getStrength() {
    return strength;
}

int ability::getLife() {
    return life;
}

int ability::random() {
    int n;
    n = ((rand() % 10) + 1);
    return n;
}

string ability::to_str() {
    string s;
    char b[3];
    s = "Life: ";
    sprintf(b, "%d", life);
    s += b;
    s = "\nStrength: ";
    sprintf(b, "%d", strength);
    s += b;
    s = "\nIntel: ";
    sprintf(b, "%d", intelligence);
    s += b;
    s += "\n";
}
