#ifndef WEAPONS_H
#define WEAPONS_H

#include <list>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

class weapons
{
    public:
        weapons();
        virtual ~weapons();
        //genera un nome casuale per l'oggetto trovato
        string weap_name();
        string getName();
        int getValue();

        int random();

private:
       string weap;
        int value;

};

#endif // WEAPONS_H
