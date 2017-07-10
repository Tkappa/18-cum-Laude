/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Controller.h
 * Author: Master
 *
 * Created on 13 maggio 2017, 12.12
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
//#include "../model/pc/Character.hpp"
#include "../model/npc/Follower.hpp"
#include "../model/pc/MajorCharacter.hpp"
#include "../view/mappa/Mappa.h"
#include "../view/View.h"
#include "../model/pc/inventory.hpp"
#include <queue>

using namespace std;

class Controller {
protected:
//    MajorCharacter pg;
//    Follower* gino;
//    Mappa map;
//    View vista;
private:
    queue<char*> narrative;
public:
    Controller(int nLevels);
    void launch();
    void testFollower();
    void testAttack();
    void dati(char buf[]);
    void movement(int dir);
    MajorCharacter pgInitialization(View curview);
    //da rimuovere e mettere nella gestione degli input
    void loot(p_char pg, Map* curMap);
    bool drop(p_char pg,char c,Map* curMap);
    bool equip(p_char pg, char c);
};

#endif /* CONTROLLER_H */

