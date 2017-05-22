#ifndef ABILITY_H
#define ABILITY_H

#include<ctime>
#include<cstdlib>

class ability
{
    public:
        ability();
        virtual ~ability();
    //inizializza le abilita del personaggio in base alla facolta scelta
        void setIntelligence(int n);
        int getIntelligence();
        void setStrength(int n);
        int getStrength();
        int getLife();

      //Restituisce un numero random per int e soc
        int /*abstract*/ random();

    private:
        int intelligence;
        int strength;
        int life;
};

#include "ability.cpp"
#endif // ABILITY_H
