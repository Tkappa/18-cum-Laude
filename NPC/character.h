#include <string>

#ifndef CHARACTER_INTERFACE
#define CHARACTER_INTERFACE

typedef struct position {
    int xPos;
    int yPos;
} POS;

typedef struct statistcs {
    int life;
    int strength;
    int intelligence;
} STATS;

class character {
protected:
    // parametri di esempio che poi saranno cambiati
    STATS statistics;

    bool alive;

    // posizione corrente
    POS currentPosition;

public:
    character(STATS params, POS position) ;

    character(STATS params) ;

    void attacca(character * otherCharacter) ;

    // probabilmente sarà eliminato e realizzato da Igor
    bool muovi(int direction) ;

    // stabilisce in che direzione muoversi per avvicinarsi al personaggio passato come parametro
    // ritorna l'intero che indica la direzione in cui muoversi
    int muoviVersoPersonaggio(character otherCharacter) ;

    POS getPos() ;

    // definito virtual per poter essere sovrascritto dalle classi derivate
    virtual void setPos(POS newPosition) ;

    bool isAlive() ;

    int getLife() ;

    int getStrength() ;

    int getIntelligence() ;

    virtual std::string toString() ;
};


#endif // CHARACTER_INTERFACE
