//
// Created by Stefano Andriolo on 11/04/17.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_CHARACTER_H

typedef struct position {
    int xPos;
    int yPos;
} POS;

typedef POS * pos;

class character {
protected:
    // parametri di esempio che poi saranno cambiati
    int life;
    int strength;
    int intelligence;

    bool alive;

    // posizione corrente
    pos currentPosition;

public:
    character(int life, int strength, int intelligence) ;

    void attacca(character otherCharacter) ;

    // probabilmente sarà eliminato e realizzato da Igor
    bool muovi(int direction) ;

    // stabilisce in che direzione muoversi per avvicinarsi al personaggio passato come parametro
    // ritorna l'intero che indica la direzione in cui muoversi
    int muoviVersoPersonaggio(character otherCharacter) ;

    pos getPos() ;

    void setPos(pos newPosition) ;

    bool isAlive() ;

    int getLife() ;

    int getStrength() ;

    int getIntelligence() ;
};


#endif //PROGETTO_PROGRAMMAZIONE_CHARACTER_H
