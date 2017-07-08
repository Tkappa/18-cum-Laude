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

enum Direction {
    left = 1, up, right, down
};

typedef struct mapPos {
    int mapX, mapY, stanzX, stanzY;
} Pos;

//typedef struct Statistics {
  //  int life, strength, intelligence;
//} Stats;


#endif /* ENVIRONMENT_HPP */

