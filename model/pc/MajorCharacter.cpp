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
    /*sprintf(buf, "%d", this->getStats().getLife());
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
*/
    return s;
}



 MajorCharacter::MajorCharacter(bioma currentZone, int currentLevel) {
    srand(time(nullptr));
    cout<<"Sono nel costruttore del majorchar"<<endl;
    // la somma dei valori delle statistiche del personaggio viene impostata in relazione al livello
    // ed il suo valore si discosta dal livello per al massimo un terzo del valore di quest'ultimo
    int deltaStats = currentLevel / 3;

    // con questa formula la vita differisce di +- 1/3 rispetto al livello corrente
    cout<<"sto per calcolare statsAmount"<<endl;
    int statsAmount = 1;
    //currentLevel + ((rand() % (deltaStats * 2)) + 1 - deltaStats);
    cout<<"Ho fatto stats amount"<<endl;
    string filePath = SEDE_CENTRALE;

    if (currentZone == centro_sociale) {
        filePath = CENTRO_SOCIALE;
    } else if (currentZone == facolta) {
        filePath = FACOLTA;
    } else if (currentZone == piazza_verdi) {
        filePath = PIAZZA_VERDI;
    }

    // ottengo i nomi contenuti nel file relativo al bioma
    auto names = readNamesFrom(filePath);

    ability stats = setUpAbilities(statsAmount);

    string name = names[rand() % names.size() + 1];
    cout<<"Ho nome e stats e sto per andare nel costruttore character";
    Character(name,stats);
    cout<<"Sono uscito dal costruttore charachter";
}


vector<string> MajorCharacter::readNamesFrom(string fileName) {

    // apro lo stream verso il file selezionato
    ifstream infile(fileName);
    if(!infile){
        cout<<endl<<"Non esiste il file"<<endl;
    }
    // vettore contenente tutti i nomi dei file
    vector<string> names;

    string currentLine;
    while (getline(infile, currentLine)) {
        names.push_back(currentLine);
    }

    return names;
}


ability MajorCharacter::setUpAbilities(int statsAmount) {

    srand(time(nullptr));

    // imposto le abilità del personaggio
    ability stats;

    // se la somma delle caratteristiche del personaggio è <= 3
    // assegno ad ognuna delle 3 caratteristiche il valore 1
    if (statsAmount <= 3) {
        stats.setDefense(1);
        stats.setStrength(1);
        stats.setLife(1);
    } else {
        // assegno casualmente una parte dei valori delle caratteristiche
        // se il valore fosse minore di 1, assegno 1 di default
        int intelligenceAmount = rand() % statsAmount + 1;
        stats.setDefense(intelligenceAmount < 1 ? 1 : intelligenceAmount);

        statsAmount -= intelligenceAmount;
        int strengthAmount = rand() % statsAmount + 1;
        stats.setStrength(strengthAmount < 1 ? 1 : strengthAmount);

        int lifeAmount = statsAmount - strengthAmount;
        stats.setLife(lifeAmount < 1 ? 1 : lifeAmount);
    }

    return stats;
}
