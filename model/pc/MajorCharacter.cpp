/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MajorCharacter.cpp
 * Author: Master
 * 
 * Created on 15 maggio 2017, 16.00
 */

#include <string>

using namespace std;

#include "MajorCharacter.hpp"

MajorCharacter::MajorCharacter(string n, ability s, Pos p, string d, Follower* f) : Character(n, s, p, d) {
    this->follower = f;
}

void MajorCharacter::setFollower(Follower* f) {
    this->follower = f;
}

void MajorCharacter::setPos(Pos newPos) {
    //TODO: se il personaggio non ha una posizione valida??
    if (this->follower != NULL)
        follower->setPos((Pos){this->pos.mapX, this->pos.mapY, this->pos.stanzX, this->pos.stanzY});

    this->pos = newPos;
}

string MajorCharacter::toStr() {
    char buf[5];
    string s = "Character \"" + this->name + "\": {\n\tStatistics: {\n\t\tlife: ";
    sprintf(buf, "%d", this->getStats().getLife());
    s += buf;
    s += ",\n\t\tstrength: ";
    sprintf(buf, "%d", this->getStats().getStrength());
    s += buf;
    s += ",\n\t\tintelligence: ";
    sprintf(buf, "%d", this->getStats().getIntelligence());
    s += buf;
    s += "\n\t}\n\tPos: {\n\t\tMap [ ";
    sprintf(buf, "%d", this->pos.mapX);
    s += buf;
    s += ", ";
    sprintf(buf, "%d", this->pos.mapY);
    s += buf;
    s += " ],\n";
    s += "\t\tRoom [ ";
    sprintf(buf, "%d", this->pos.stanzX);
    s += buf;
    s += ", ";
    sprintf(buf, "%d", this->pos.stanzY);
    s += buf;
    s += " ]";
    s += "\n\t}\n\tStatus: ";
    s += this->isAlive() ? "ALIVE" : "DEAD";
    s += "\n\t";
    s += this->follower != NULL ? this->follower->toStr() : "Follower: NULL";
    s += "\n}\n\n";

    return s;
}