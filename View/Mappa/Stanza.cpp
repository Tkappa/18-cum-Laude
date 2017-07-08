//
// Created by Igor Ershov on 29/03/2017.
//
#include "Stanza.h"
#include <iostream>

Room::Room(){
    //Popola la stanza con tutti vuoti, in modo che verrà stampata senza problemi
    for (int i=0;i<roomHeight ;i++){
        for (int j=0;j<roomLenght;j++){
            room[i][j]=' ';

        }
    }
    explored=false;
}

void Room::createRoom() {
    //Popola la stanza con spazi vuoti(".") a meno che non siano il primo/ultimo elemento di una riga/colonna in tal caso mette un muro("-" o "|")
    for (int i=0;i<roomHeight ;i++){
        for (int j=0;j<roomLenght;j++){
            if(i==0||i==roomHeight-1) room[i][j]='-';
            else if(j==0||j==roomLenght-1)    room[i][j]='|';
            else    room[i][j]='.';

        }
    }
}

void Room::printRoom() {
    //Stampa tutti i contenuti della matrice stanza con spazi tra loro cosi viene più bello
    for (int i = 0; i < roomHeight ; i++) {
        for (int j = 0; j < roomLenght ; j++) {
            std::cout << room[i][j];
            std::cout<<" ";
        }
        std::cout<<"\n";
    }
}

//direzione è il lato in cui verrà creata la porta, 1=sinista,2=su,3=destra,4=giu
void Room::createDoor(int Direction){
    //Avevo dimenticato che esistevano gli switch , che bel mondo in cui viviamo
    switch (Direction){
        case 1: //sinistra
            room[roomHeight/2][0]='.';
            break;
        case 2: //su
            room[0][roomHeight/2]='.';
            break;
        case 3: //destra
            room[roomHeight/2][roomLenght-1]='.';
            break;
        case 4: //giu
            room[roomHeight-1][roomLenght/2]='.';
            break;
    }
}

void Room::createPos(int x,int y,std::string symbol){
    //aggiorna la posizione
    room[x][y]=symbol[0];
}

char Room::getValue(int x,int y){
    return room[y][x];
}
bool Room::exists(){
    if(room[0][0]==' ') return false;
    else return true;
};
bool Room::canMove(int x,int y,int dir){
    switch(dir){
case 1:
    //sinistra
    if(x==roomHeight/2 && y==0)
        return true;
    else if(room[x][y-1]!='|'&&room[x][y-1]!='-')
        return true;
    else
        return false;
    break;
case 2:
    //su
    if(x==0 && y==roomLenght/2)
        return true;
    else if(room[x-1][y]!='|'&&room[x-1][y]!='-')
        return true;
    else
        return false;
    break;
case 3:
    //destra
    if(x==roomLenght/2 && y==roomHeight-1)
        return true;
    else if(room[x][y+1]!='|' && room[x][y+1]!='-')
        return true;
    else
        return false;
    break;
case 4:
    //giu
    if(x==roomLenght-1 && y==roomHeight/2 )
        return true;
    else if(room[x+1][y]!='|' && room[x+1][y]!='-')
        return true;
    else
        return false;
    break;
    }
};
void Room::exploration(){
    explored=true;
}
bool Room::isExplored(){
    return explored;
    }
