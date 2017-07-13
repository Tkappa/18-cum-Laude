/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   environment.hpp
 * Author: Master
 *
 * Created on 16 maggio 2017, 15.32
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#define DEBUG


#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <queue>

//Definizioni per la modalità di accesso all'inventario
#define SEE 1
#define DROP 2
#define EQUIP 3
#define BUY 4

//Definizioni per le tipologie di oggetti
#define ITEM 0
#define ARMOR 2
#define WEAPON 1
#define MONEY 3
#define POTION 4



using namespace std;
//Definizione di direzione usato per il personaggio pricipale
enum Direction {
    stop=0 ,left = 1, up, right, down
};

//definizione di mapPos usato per ogni oggetto
typedef struct mapPos {
    int mapX, mapY, stanzX, stanzY;
} Pos;

//Definizione di bioma usata nella creazione di un npc
enum bioma {
    open_day = 1, facolta, piazza_verdi, sede_centrale
};

#endif /* ENVIRONMENT_HPP */

