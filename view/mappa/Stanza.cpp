//
// Created by Igor Ershov on 29/03/2017.
//
#include "Stanza.h"
#include <iostream>

Stanza::Stanza(){
    //Popola la stanza con tutti vuoti, in modo che verrà stampata senza problemi
    for (int i=0;i<altezzaStanza ;i++){
        for (int j=0;j<lunghezzaStanza;j++){
            stanza[i][j]=' ';

        }
    }
    esplorata=false;
}

void Stanza::creaStanza() {
    //Popola la stanza con spazi vuoti(".") a meno che non siano il primo/ultimo elemento di una riga/colonna in tal caso mette un muro("-" o "|")
    for (int i=0;i<altezzaStanza ;i++){
        for (int j=0;j<lunghezzaStanza;j++){
            if(i==0||i==altezzaStanza-1) stanza[i][j]='-';
            else if(j==0||j==lunghezzaStanza-1)    stanza[i][j]='|';
            else    stanza[i][j]='.';

        }
    }
}

void Stanza::stampaStanza() {
    //Stampa tutti i contenuti della matrice stanza con spazi tra loro cosi viene più bello
    for (int i = 0; i < altezzaStanza ; i++) {
        for (int j = 0; j < lunghezzaStanza ; j++) {
            std::cout << stanza[i][j];
            std::cout<<" ";
        }
        std::cout<<"\n";
    }
}

//direzione è il lato in cui verrà creata la porta, 1=sinista,2=su,3=destra,4=giu
void Stanza::creaPorta(int direzione){
    //Avevo dimenticato che esistevano gli switch , che bel mondo in cui viviamo
    switch (direzione){
        case 1: //sinistra
            stanza[altezzaStanza/2][0]='.';
            break;
        case 2: //su
            stanza[0][lunghezzaStanza/2]='.';
            break;
        case 3: //destra
            stanza[altezzaStanza/2][lunghezzaStanza-1]='.';
            break;
        case 4: //giu
            stanza[altezzaStanza-1][lunghezzaStanza/2]='.';
            break;
    }
}

void Stanza::creaPos(int x,int y,char carattere){
    //controlla se collide con qualcosa che non sia uno spazio "vuoto"(".") e solo se non collide aggiorna la posizione
    //if(stanza[x][y]=='.')
    stanza[x][y]=carattere;
}

char Stanza:: getValue(int x,int y){
    return stanza[y][x];
}
bool Stanza::esiste(){
    if(stanza[0][0]==' ') return false;
    else return true;
};
bool Stanza::canMove(int x,int y,int dir){
    switch(dir){
case 1:
    //sinistra
    if(x==altezzaStanza/2 && y==0)
        return true;
    else if(stanza[x][y-1]!='|'&&stanza[x][y-1]!='-')
        return true;
    else
        return false;
    break;
case 2:
    //su
    if(x==0 && y==lunghezzaStanza/2)
        return true;
    else if(stanza[x-1][y]!='|'&&stanza[x-1][y]!='-')
        return true;
    else
        return false;
    break;
case 3:
    //destra
    if(x==lunghezzaStanza/2 && y==altezzaStanza-1)
        return true;
    else if(stanza[x][y+1]!='|' && stanza[x][y+1]!='-')
        return true;
    else
        return false;
    break;
case 4:
    //giu
    if(x==lunghezzaStanza-1 && y==altezzaStanza/2 )
        return true;
    else if(stanza[x+1][y]!='|' && stanza[x+1][y]!='-')
        return true;
    else
        return false;
    break;
    }
};
void Stanza::esplorazione(){
    esplorata=true;
}
bool Stanza::isEsplorata(){
    return esplorata;
    }
