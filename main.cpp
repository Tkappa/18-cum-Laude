#include <cstdlib>
#include "control/Controller.h"

int main(int argc, char *argv[]) {
    Controller c(10);
    c.launch();
//    c.testFollower();
//    c.testAttack();
    return 0;
}
