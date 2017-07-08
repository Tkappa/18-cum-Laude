/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Aiutante.hpp
 * Author: Master
 *
 * Created on 13 maggio 2017, 20.21
 */

#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include "../pc/Character.hpp"

class Follower : public Character {
public:
    Follower();
    Follower(string n, ability s);
    virtual string toStr();
private:

};

#endif /* FOLLOWER_HPP */

