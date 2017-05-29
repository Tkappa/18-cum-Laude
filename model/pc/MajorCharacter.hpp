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

#include <string>
#include "Character.hpp"
#include "../npc/Follower.hpp"

using namespace std;

class MajorCharacter : public Character {
public:
//    MajorCharacter();
//    MajorCharacter(string n, ability s);
//    MajorCharacter(string n, ability s, Pos p);
//    MajorCharacter(string n, ability s, Pos p, string d);
    MajorCharacter(string n, ability s, Pos p, string desc, Follower* f);
    void setFollower(Follower* f);
    void setPos(Pos newPos);
//    string string toStr() override;
    string toStr();

protected:
    Follower* follower;
};

#endif /* MAJORCHARACTER_HPP */

