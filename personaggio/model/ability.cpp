
#include "ability.h"

using namespace std;

ability::ability()
{
    this->intelligence=0;
    this->strength=0;
    this->life=10;
}

void ability:: setIntelligence(int n){
    this->intelligence=n;
}
void ability:: setStrength(int n){
    this->strength=n;
}
int ability:: getIntelligence(){
    return intelligence;
}
int ability:: getStrength(){
    return strength;
}
int ability:: getLife(){
    return life;
}
int ability::random(){
    int n;
    n=((rand()%10)+1);
    return n;
}


ability::~ability()
{
    //dtor
}
