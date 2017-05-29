/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Follower.cpp
 * Author: Master
 * 
 * Created on 13 maggio 2017, 20.21
 */

#include "Follower.hpp"

Follower::Follower() : Character() {}
Follower::Follower(string n, ability s) : Character(n, s) {}

string Follower::toStr() {
    char buf[5];
    string s = "Follower \"" + this->name + "\": {\n\tStatistics: {\n\t\tlife: ";
    sprintf(buf, "%d", this->getStats().getLife());
    s += buf;
    s += ",\n\t\tstrength: ";
    sprintf(buf, "%d", this->getStats().getStrength());
    s += buf;
    s += ",\n\t\tintelligence: ";
    sprintf(buf, "%d", this->getStats().getIntelligence());
    s += buf;
    s += "\n\t}\n\tPos: {\n\t\tx: ";
    sprintf(buf, "%d", this->pos.mapX);
    s += buf;
    s += ",\n\t\ty: ";
    sprintf(buf, "%d", this->pos.mapY);
    s += buf;
    s+="\n\t}\n\tStatus: ";
    s += this->isAlive() ? "ALIVE" : "DEAD";
    s += "\n}\n\n";

    return s;
}

