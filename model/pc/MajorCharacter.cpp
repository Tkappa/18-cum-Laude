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

#include "MajorCharacter.hpp"

//Vettori contenenti i nomi dei vari personaggi che possono apparire

vector<string> V_OPEN_DAY = { "Liceale",  "Professore che dice bugie",  "Reclutatore",  "Universitario stanco",
                                  "Universitario",  "Professore che di vanta",  "Informazioni strane",  "Costo della vita",};

vector<string> V_SEDE_CENTRALE = { "Segretaria",  "Vicario",  "Vice Rettore",  "Orale con il professore",
                                 "Orari di chiusura",  "Fila alla segreteria",  "Professore in pensione",  "Sala studio piena"};

vector<string> V_FACOLTA = { "Facebook",  "Video di gatti",  "Esame impossibile",  "Lezione noiosa",
                           "Hangover di ieri",  "Voglia di andare a casa",  "Saltae la lezione",  "Fidanzata",
                           "Giochi al PC"  };

vector<string> V_PIAZZA_VERDI = { "Pakistano",  "Goliarda",  "Goliarda con il mantello",  "Pakistano con birre",
                                "Punkabbestia",  "Punkabbestio",  "Manifestante",  "Tornello",
                                "Protestante", "Marxista"  };


using namespace std;

MajorCharacter::MajorCharacter() : Character() {}

MajorCharacter::MajorCharacter(string n, ability s) : Character(n, s) {
}

MajorCharacter::MajorCharacter(int currentZone, int currentLevel) : MajorCharacter() {
    // la somma dei valori delle statistiche del personaggio viene impostata in relazione al livello
    // ed il suo valore si discosta dal livello per al massimo un terzo del valore di quest'ultimo

    auto namesVector = V_SEDE_CENTRALE;

    if (currentZone == open_day) {
        namesVector = V_OPEN_DAY;
    } else if (currentZone == facolta) {
        namesVector = V_FACOLTA;
    } else if (currentZone == piazza_verdi) {
        namesVector = V_PIAZZA_VERDI;
    }

    ability stats = setUpAbilities(currentLevel);

    string name = namesVector[rand() % namesVector.size()];
    string symb=name.substr(0,1);

    this->setSym(symb);
    this->name = name;
    this->setStats(stats);
    this->setFullStats(stats);
 }

void MajorCharacter::setPos(Pos newPos) {
    this->pos = newPos;
}

ability MajorCharacter::setUpAbilities(int curLevel) {


    // imposto le abilità del personaggio
    ability stats;

    //Di quanto può differire il valore dalla statistica base in positivo o negativo

    int difference=2;

    //la statistica base che permette che gli npc diventino sempre più forti andando avanti
    int base=1+curLevel;

    //(rand()%(difference*2))-difference fa in modo che i valori possano essere anche negativi
    int intelligenceAmount = base+(rand()%(difference*2))-difference;
    int strengthAmount = base+(rand()%(difference*2))-difference;
    int lifeAmount = 3*(base+(rand()%(difference*2))-difference);

    stats.setDefense(intelligenceAmount);
    stats.setStrength(strengthAmount);
    stats.setLife(lifeAmount);

    return stats;
}
