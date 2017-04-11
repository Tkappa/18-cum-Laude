#include <string>
#include "character.h"
#include "aiutante.h"
using namespace std;


#ifndef MAJORCHARACTER_INTERFACE
#define MAJORCHARACTER_INTERFACE


class majorCharacter : public character {

protected:
    string name;
    string description;

    // metodo da richiamare all'update della posizione del personaggio
    aiutante * follower;

public:
    majorCharacter(string name, string description, STATS params) ;

    majorCharacter(string name, string description, STATS params, POS position) ;

    majorCharacter(string name, string description, STATS params, POS position, aiutante * follower) ;

    // imposta l'aiutante passato come follower del personaggio corrente (l'aiutante segue il personaggio)
    void setFollower(aiutante * follower) ;

    // overriding del metodo ereditato
    void setPos(POS newPos) ;

    string toString() ;

    string getName() ;

    string getDescription() ;
};






#endif // MAJORCHARACTER_INTERFACE
