#include <cstdlib>
#include "control/Controller.h"
#include <stdio.h>
using namespace std;


int main(int argc, char *argv[]) {
    Controller c(10);
    c.launch();

//    c.testFollower();
//    c.testAttack();

    return 0;
}

/*#include <cstdlib>
#include "control/Controller.h"
#include <stdio.h>
#include <vector>
#include "model/pc/MajorCharacter.hpp"

int main(int argc, char *argv[]) {

    vector<MajorCharacter> mcs(0);

    mcs.push_back(MajorCharacter::MajorCharacter(centro_sociale, 10));
    mcs.push_back(MajorCharacter(piazza_verdi, 3));
    mcs.push_back(MajorCharacter(sede_centrale, 45));
    mcs.push_back(MajorCharacter(piazza_verdi, 100));
    mcs.push_back(MajorCharacter(facolta, 25));
    mcs.push_back(MajorCharacter(sede_centrale, 73));
    mcs.push_back(MajorCharacter(centro_sociale, 1));
    mcs.push_back(MajorCharacter(facolta, 31));

    for (MajorCharacter character : mcs) {
        cout << character.toStr() << endl;
    }

    return 0;
}*/
