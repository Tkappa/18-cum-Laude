//
// Created by Igor Ershov on 05/04/2017.
//

#include "Stanza.h"
#include "Mappa.h"
#include <iostream>
#include <time.h>

Mappa::Mappa(int n){

    srand(time(NULL));
    int stanzeAggiuntive= n +(rand()%3+1);
    mappa[1][3].creaStanza();
}

void  Mappa::stampaMappa(){
    for (int i=0;i<altezzaMappa ;i++){
        for (int j=0;j<lunghezzaMappa;j++){
            mappa[i][j].stampaStanza();
        }
        std::cout<<"\n";
    }
}