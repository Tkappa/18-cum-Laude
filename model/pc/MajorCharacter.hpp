/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MajorCharacter.hpp
 * Author: Master
 *
 * Created on 15 maggio 2017, 16.00
 */

#ifndef MAJORCHARACTER_HPP
#define MAJORCHARACTER_HPP

#include "Character.hpp"
#include "ability.h"
#include "../../environment.hpp"

using namespace std;




class MajorCharacter : public Character {
public:

    MajorCharacter();
    //Costruttore Randomico
    MajorCharacter(int a,int nLivelli);

    //Costruttore per il personaggio principale
    MajorCharacter(string n, ability s);

    void setPos(Pos newPos);

private:
    static ability setUpAbilities(int curLevel);
};

#endif /* MAJORCHARACTER_HPP */
