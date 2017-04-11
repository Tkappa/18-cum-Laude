#include "aiutante.h"
#include "character.h"
#include <string>
using namespace std;

aiutante::aiutante(STATS params) : character(params) { }

string aiutante::toString() {
    string s = "Aiutante - life: ";
    s += to_string(this->statistics.life);
    s += ", strength: ";
    s += to_string(this->statistics.strength);
    s += ", intelligence: ";
    s += to_string(this->statistics.intelligence);
    s += ", xPos: ";
    s += to_string(this->currentPosition.xPos);
    s += ", yPos: ";
    s += to_string(this->currentPosition.yPos);
    s += this->isAlive() ? ", ALIVE" : ", DEAD";

    return s;
}
