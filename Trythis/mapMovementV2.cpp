#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>

using namespace std;

#include "libsqlite.hpp"
#include "unitMovement.h"
#include "main.h"

void UnitMovement::show_Values(){ /* ----------------- THIS FUNCTION IS USED JUST TO SHOW WHAT IS HAPPENING ----------------- */
    string File = "civilwarofMalibu.db";
    cout << "\033[2J\033[1;1H";
    
    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT ID, Owned, Soldiers FROM Map; "); 
                     // "WHERE Owned = ?;");
        
        cur->prepare();
        //cur->bind(1,"1");
        while(cur->step()){
            int ID = cur->get_int(0);
            string Owned = cur->get_text(1);
            int Soldiers = cur->get_int(2);
            cout << ID << " " << Owned << " " << Soldiers << endl;
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

int UnitMovement::from_Input(){
    show_Values();
    int movefrom_Input;
    cout << "Move units from: ";
    cin >> movefrom_Input;
    cout << "\033[2J\033[1;1H";
    return movefrom_Input;
}

int UnitMovement::to_Input(){
    show_Values();
    int moveto_Input;
    cout << "Move units to: ";
    cin >> moveto_Input;
    cout << "\033[2J\033[1;1H";
    return moveto_Input;
}

void UnitMovement::move_Soldiers(){
    
    Menu menu;
    
    string File = "civilwarofMalibu.db";
    int units_Input;
    int movefrom_Input;
    int moveto_Input;
    
    movefrom_Input = from_Input(); 
    
    if(movefrom_Input <= 10){
        moveto_Input = to_Input();
        if(moveto_Input <= 10){
            show_Values();
            cout << "How many units? ";
            cin >> units_Input;

            try{
                sqlite::sqlite db( File );
                auto cur1 = db.get_statement();
                auto cur2 = db.get_statement();
                auto cur3 = db.get_statement();
                auto cur4 = db.get_statement();


                /* ----------------- THIS IS THE QUERY THAT CHECKS WHERE THE USER WANTS TO MOVE TO ----------------- */
                cur1->set_sql( "SELECT Soldiers, Owned FROM Map "
                               "WHERE ID = ?;");

                cur1->prepare();
                cur1->bind(1, moveto_Input);
                cur1->step();
                int id_To = cur1->get_int(0);
                string owned_To = cur1->get_text(1);


                /* ----------------- THIS IS THE QUERY THAT CHECKS WHERE THE USER WANTS TO MOVE FROM ----------------- */
                cur2->set_sql( "SELECT Soldiers, Owned FROM Map "
                               "WHERE ID = ?;");

                cur2->prepare();
                cur2->bind(1, movefrom_Input);
                cur2->step();
                int id_From = cur2->get_int(0);
                string owned_From = cur1->get_text(1);


                int transfer_Amount = id_From - units_Input; 
                int new_Amount = id_To + units_Input;

                if(transfer_Amount > 0){/* THIS CHECKS IF MOVING THE UNITS WILL SEND THE AREA INTO NEGATIVE VALUES - CAUSING UNIT DUPLICATION AND POTENTIALLY BREAKING THE COMBAT */
                    if((owned_To == "1")&&(owned_From == "1")){/* THIS CHECKS TO ENSURE THE USER CAN'T MOVE UNITS TO AND FROM TERRITORIES THAT AREN'T OWNED */


                        /* ----------------- THIS IS THE QUERY THAT UPDATES MOVING TO A LOCATION ----------------- */
                        cur3->set_sql( "UPDATE Map "
                                       "SET Soldiers = ? WHERE Owned = '1' AND ID = ?");

                        cur3->prepare();
                        cur3->bind(1,new_Amount);
                        cur3->bind(2,moveto_Input);
                        cur3->step();

                        /* ----------------- THIS IS THE QUERY THAT UPDATES MOVING FROM A LOCATION ----------------- */
                        cur4->set_sql( "UPDATE Map "
                                       "SET Soldiers = ? WHERE Owned = '1' AND ID = ?");

                        cur4->prepare();
                        cur4->bind(1,transfer_Amount);
                        cur4->bind(2,movefrom_Input);
                        cur4->step();
                        
                        cout << "\033[2J\033[1;1H";
                    }
                    else{
                        cout << "YOU DON'T OWN ONE OF THOSE TERRITORIES" << endl;
                        sleep(1);
                        cout << "\033[2J\033[1;1H";
                        show_Values();
                        move_Soldiers();
                    }
                }
                else{
                    cout << "Insufficient amount of units" << endl;
                    sleep(1);
                    cout << "\033[2J\033[1;1H";
                    show_Values();
                    move_Soldiers();
                }
            }
            catch( sqlite::exception e){
                std::cerr << e.what() << endl;

            }
        }
        else{
            menu.main_Menu();
        }
    }
    else{
        menu.main_Menu();      
    }
}
        


void UnitMovement::execute(){
    move_Soldiers();
}