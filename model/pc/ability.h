#ifndef ABILITY_H
#define ABILITY_H

#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

class ability {
public:
    ability();
    //inizializza le abilita del personaggio in base alla facolta scelta
    void setDefense(int n);
    int getDefense();
    void setStrength(int n);
    int getStrength();
    int getLife();
    void setLife(int n);

    //Restituisce un numero random per int e soc
    int /*abstract*/ random();

    string to_str();

protected:
    int defense;
    int strength;
    int life;
};

//#include "ability.cpp"
#endif // ABILITY_H
