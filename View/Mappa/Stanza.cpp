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

//direzione è il lato in cui verrà creata la porta, 0=sinista,1=su,2=destra,3=giu
void Stanza::creaPorta(int direzione){
    //TODO:Fare delle porte invece che aperture? Magari che si aprono con chiavi?
    //Avevo dimenticato che esistevano gli switch , che bel mondo in cui viviamo
    switch (direzione){
        case 0: //sinistra
            stanza[altezzaStanza/2][0]='.';
            break;
        case 1: //su
            stanza[0][lunghezzaStanza/2]='.';
            break;
        case 2: //destra
            stanza[altezzaStanza/2][lunghezzaStanza-1]='.';
            break;
        case 3: //giu
            stanza[altezzaStanza-1][lunghezzaStanza/2]='.';
            break;
    }
}

void Stanza::updatePos(int x,int y,char carattere){
    //controlla se collide con qualcosa che non sia uno spazio "vuoto"(".") e solo se non collide aggiorna la posizione
    if(stanza[x][y]=='.')stanza[x][y]=carattere;
}