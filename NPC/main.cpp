#include <string>
#include <iostream>
using namespace std;

#include "character.h"
#include "aiutante.h"
#include "majorCharacter.h"


int main() {
    // personaggio generico, probabilmente non sarà mai usato direttamente
    character personaggio ((STATS) {12, 10, 5});
    cout << personaggio.toString() << endl << endl;

    // personaggio maggiore, può essere sia un personaggio alleato che un nemico
    majorCharacter mago ("Merlino", "Un mago molto potente", (STATS) {10, 5, 20}, (POS) {7, 3});

    majorCharacter drago ("Drago bianco occhi blu", "Un drago molto potente", (STATS) {50, 20, 1}, (POS) {1, 5});
    cout << drago.toString() << endl << '\t' << drago.getDescription() << endl << endl;


    aiutante temp ((STATS) {2, 5, 3});
    aiutante *elfo = &temp;

    mago.setFollower(elfo);

    cout << mago.toString() << endl << '\t' << mago.getDescription() << endl << endl;


    drago.attacca(&mago);
    cout << mago.toString() << endl
        << drago.toString() << endl;

    return 0;
}