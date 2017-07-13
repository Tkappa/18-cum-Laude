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
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

#include "MajorCharacter.hpp"
#include "ability.h"

using namespace std;


vector<string> OPEN_DAY = { "CentroSociale1",  "CentroSociale2",  "CentroSociale3",  "CentroSociale4",
                                  "CentroSociale5",  "CentroSociale6",  "CentroSociale7",  "CentroSociale8",
                                  "CentroSociale9"  };

vector<string> SEDE_CENTRALE = { "SedeCentrale1",  "SedeCentrale2",  "SedeCentrale3",  "SedeCentrale4",
                                 "SedeCentrale5",  "SedeCentrale6",  "SedeCentrale7",  "SedeCentrale8",
                                 "SedeCentrale9"  };

vector<string> FACOLTA = { "Facolta1",  "Facolta2",  "Facolta3",  "Facolta4",
                           "Facolta5",  "Facolta6",  "Facolta7",  "Facolta8",
                           "Facolta9"  };

vector<string> PIAZZA_VERDI = { "PiazzaVerdi1",  "PiazzaVerdi2",  "PiazzaVerdi3",  "PiazzaVerdi4",
                                "PiazzaVerdi5",  "PiazzaVerdi6",  "PiazzaVerdi7",  "PiazzaVerdi8",
                                "PiazzaVerdi9"  };


MajorCharacter::MajorCharacter() : Character() {}

MajorCharacter::MajorCharacter(string n, ability s) : Character(n, s) {
    this->follower = NULL;
}

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
    sprintf(buf, "%d", this->basestats.getLife());
    s += buf;
    s += ",\n\t\tstrength: ";
    sprintf(buf, "%d", this->basestats.getStrength());
    s += buf;
    s += ",\n\t\tintelligence: ";
    sprintf(buf, "%d", this->basestats.getDefense());
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



 MajorCharacter::MajorCharacter(bioma currentZone, int currentLevel) : MajorCharacter() {
    // la somma dei valori delle statistiche del personaggio viene impostata in relazione al livello
    // ed il suo valore si discosta dal livello per al massimo un terzo del valore di quest'ultimo
    /*int deltaStats = currentLevel / 2;

    // con questa formula la statistiche differiscono di +- 1/3 rispetto al livello corrente con possibilità di valori alti dal random
    int amount = currentLevel+1-deltaStats;
    int randamont = deltaStats != 0 ? rand() % deltaStats * 2 : 0;
    //Parte da 10 in modo che siano simili al personaggio come statistiche iniziali
    int statsAmount = 10+amount+randamont;
    */
    auto namesVector = SEDE_CENTRALE;

    if (currentZone == open_day) {
        namesVector = OPEN_DAY;
    } else if (currentZone == facolta) {
        namesVector = FACOLTA;
    } else if (currentZone == piazza_verdi) {
        namesVector = PIAZZA_VERDI;
    }

    ability stats = setUpAbilities(currentLevel);

    string name = namesVector[rand() % namesVector.size()];
    string symb=name.substr(0,1);

    this->setSym(symb);
     this->name = name;
     this->setStats(stats);
     this->setFullStats(stats);
     this->follower = NULL;
 }


ability MajorCharacter::setUpAbilities(int curLevel) {


    // imposto le abilità del personaggio
    ability stats;

    //Di quanto può differire il valore dalla statistica base in positivo o negativo

    int difference=2;

    //la statistica base che permette che gli npc diventino sempre più forti andando avanti
    int base=2+curLevel;

    int intelligenceAmount = base+(rand()%(difference*2))-difference;
    int strengthAmount = base+(rand()%(difference*2))-difference;
    int lifeAmount = 3*(base+(rand()%(difference*2))-difference);

    stats.setDefense(intelligenceAmount);
    stats.setStrength(strengthAmount);
    stats.setLife(lifeAmount);

    return stats;
}
