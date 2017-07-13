#ifndef ABILITY_H
#define ABILITY_H

#include "../../environment.hpp"

using namespace std;

class ability {
public:
    ability();

    //setter e getter delle varie abilita
    void setDefense(int n);
    int getDefense();

    void setStrength(int n);
    int getStrength();


    void setLife(int n);
    int getLife();


protected:
    int defense;
    int strength;
    int life;
};

//#include "ability.cpp"
#endif // ABILITY_H
