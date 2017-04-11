#include "character.h"
#include <string>

#ifndef AIUTANTE_INTERFACE
#define AIUTANTE_INTERFACE

class aiutante : public character {
protected:

public:

    aiutante(STATS params) ;

    std::string toString() ;
};


#endif // AIUTANTE_INTERFACE
