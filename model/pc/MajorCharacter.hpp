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

/*
#define CENTRO_SOCIALE "../model/res/centro_sociale.txt"
#define FACOLTA "../model/res/facolta.txt"
#define PIAZZA_VERDI "../model/res/piazza_verdi.txt"
#define SEDE_CENTRALE "../model/res/sede_centrale.txt"
 */

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Character.hpp"
#include "../npc/Follower.hpp"

using namespace std;

enum bioma {
    centro_sociale = 1, facolta, piazza_verdi, sede_centrale
};


class MajorCharacter : public Character {
public:
    MajorCharacter();
    MajorCharacter(bioma a,int nLivelli);
    MajorCharacter(string n, ability s);
//    MajorCharacter(string n, ability s, Pos p);
//    MajorCharacter(string n, ability s, Pos p, string d);
    MajorCharacter(string n, ability s, Pos p, string desc, Follower* f);
    void setFollower(Follower* f);
    void setPos(Pos newPos);
//    string string toStr() override;
    string toStr();

protected:
    Follower* follower;

private:
    static ability setUpAbilities(int statsAmount);
};

#endif /* MAJORCHARACTER_HPP */
