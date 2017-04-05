//
// Created by Igor Ershov on 05/04/2017.
//

#ifndef MAPPA_MAPPA_H
#define MAPPA_MAPPA_H

#include "Stanza.h"
const int altezzaMappa=3,lunghezzaMappa=5;
class Mappa{
    protected:
        Stanza mappa[altezzaMappa][lunghezzaMappa];
    public:
        Mappa(int nLivelliPrec);
        void  stampaMappa();

};


#include "Mappa.cpp"
#endif //MAPPA_MAPPA_H
