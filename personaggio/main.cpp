#include<iostream>
#include<conio.h>
#include<string>
#include "./model/pg.h"
#include <cstdlib>
#include<ctime>
//#include "./model/ability.h"
//#include "./model/weapons.h"
//#include "./model/inventory.h"

using namespace std;



int main(){
    char start,f;
    string name;
    srand(time(0));
    cout<<"Welcome to University game! "<<endl<<"Press 's' to start the game."<<endl<<"press 'q' if want to quit";
    cin>>start;
    if(start == 'q')
        return 0;
    else {
        cout<<"insert a nickname: ";
        cin>>name;

        pg pers(name);


        cout<<"choose : "<<endl<<endl
        <<'\t'<<"a= Faculty of Physics"<<endl
            <<'\t'<<"b= Faculty of Letters"<<endl
                <<'\t'<<"c= Faculty of Law"<<endl
                    <<'\t'<<"d= Faculty of Computer Science"<<endl;
        cin>>f;
        pers.setup_character(f);



        weapons a;
        weapons b;
        weapons c;
        pers.setupInventory(b);
        pers.setupInventory(a);
        pers.setupInventory(c);

        pers.getinfo();
        string str=a.getName();
       // pers.modificaInv(str);
        //pers.getinfo();


    }
    getch();
    return 0;
}
