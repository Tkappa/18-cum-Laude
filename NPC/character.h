//
// Created by Stefano Andriolo on 11/04/17.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_CHARACTER_H


class character {
protected:
    // parametri di esempio che poi saranno cambiati
    int life;
    int strength;
    int intelligence;

    bool alive;

    // posizione corrente
    int xPos;
    int yPos;

public:
    character(int life, int strength, int intelligence) ;

    void attacca(character otherCharacter) ;

    // probabilmente sarà eliminato e realizzato da Igor
    bool muovi(int direction) ;

    int getXPos() ;

    int getYPos() ;

    void setXPos(int newX) ;

    void setYPos(int newY) ;

    bool isAlive() ;

    int getLife() ;

    int getStrength() ;

    int getIntelligence() ;
};


#endif //PROGETTO_PROGRAMMAZIONE_CHARACTER_H
