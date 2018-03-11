#include <iostream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <unistd.h>
using namespace std;
#include "libsqlite.hpp"

#include "unitMovement.h"
#include "main.h"
#include "db.h"

void Menu::menu_militaryUnits(){
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM military_Units ");
        
        int user_Input;
        while(user_Input != 1||2||3||4){
            
        cur->prepare();
        cout << "Name" << setfill(' ') << setw(19) << "Atk   " << "Def   " << "Cost" << endl; 
        cout << "---------------------------------------" << endl; 
        
        while(cur->step()){
            int ID = cur->get_int(0);
            string Name = cur->get_text(1);
            int Attack = cur->get_int(2);
            int Defence = cur->get_int(3);
            int Cost = cur->get_int(4); 
            Name.append(16 - Name.length(),' ');
            
            cout << ID << ": " << Name << setfill(' ') << setw(4) << Attack << setfill(' ') << setw(6) << Defence << setfill(' ') << setw(7) << Cost << endl;
        }
        cout << "5: Exit to menu" << endl;
            cout << "What would you like to purchase? ";
            cin >> user_Input;
            cout << "\033[2J\033[1;1H";
        
            if(user_Input == 1){
                cout << "You have purchased a Soldier! " << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 2){
                cout << "You have purchased a Bike!" << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 3){
                cout << "You have purchased a Tank!" << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 4){
                cout << "You have purchased an XCOM!" << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 5){
                break;
            }
        }
    }      
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
    

void Menu::menu_productionUnits(){
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM production_Units ");
        int user_Input;
        while(user_Input != 1||2||3||4){
            cur->prepare();
            cout << "Name" << setfill(' ') << setw(24) << "Income   " << "Cost   " << endl; 
            cout << "---------------------------------------" << endl; 

            while(cur->step()){
                int ID = cur->get_int(0);
                string Name = cur->get_text(1);
                int Income = cur->get_int(2);
                int Cost = cur->get_int(3);
                Name.append(16 - Name.length(),' ');

                cout << ID << ": " << Name << setfill(' ') << setw(6) << Income << setfill(' ') << setw(7) << Cost << endl;
            }
            cout << "4: Exit to menu" << endl;
            cout << "What would you like to purchase? ";
            cin >> user_Input;
            cout << "\033[2J\033[1;1H";
        
            if(user_Input == 1){
                cout << "You have purchased a Fishing Boat! " << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 2){
                cout << "You have purchased a Mine!" << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 3){
                cout << "You have purchased a Oil Platform!" << endl;
                sleep(1);
                break;
            }
            else if(user_Input == 4){
                sleep(1);
                break;
            }
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void Menu::store_Menu(){
    int user_Input;
    while(user_Input != 1||2||3){
        cout << "\033[2J\033[1;1H";
        cout << "Store: " << endl << "---------------------------------------" << endl << "1: Military" << endl << "2: Production" << endl << "3: Exit" << endl;
        cout << "What type of unit do you want to buy? Please enter here: ";

        cin >> user_Input;
        cout << "\033[2J\033[1;1H";
        
        switch(user_Input){
            case 1:
                menu_militaryUnits();
                break;
            case 2:
                menu_productionUnits();
                break;
            case 3:
                break;
        }
        if(user_Input == 3){
            break;
        }
    }
}
    
void Menu::main_Menu(){
    
    UnitMovement movement;
    
    
    int user_Input;
    while(user_Input != 1||2||3||4||5||6){
        cout << "\033[2J\033[1;1H";
        cout << "Menu: " << endl << "---------------------------------------" << endl << "1: Map" << endl << "2: Attack" << endl << "3: Move Units" << endl << "4: Store" << endl << "5: Save" << endl << "6: Exit" << endl;
        cout << "What do you want to do? Please enter here: ";

        cin >> user_Input;
        cout << "\033[2J\033[1;1H";
    
    switch(user_Input){
        case 1:
            cout << "ERROR 404: Map not found" << endl; //Map
            sleep(1);
            break;
        case 2:
            cout << "ERROR 404: Attack not found" << endl; //Attack
            sleep(1);
            break;
        case 3:
            movement.execute(); //Move Units
            break;
        case 4:
            store_Menu(); //Store
            break;
        case 5:
            cout << "ERROR 404: Save not found" << endl; //Save
            sleep(1);
        }
    if(user_Input == 6){ //Exit
        int user_Input;
        cout << "Are you sure you want to exit?" << endl << "1: Yes" << endl << "2: No" << endl << "Please enter here: ";
        cin >> user_Input;
        if(user_Input == 1){
            cout << "\033[2J\033[1;1H";
            break;
        }
        }
    }
}

void Menu::execute(){
    main_Menu();
        
}

int main(){
    Menu menu;
    database db;
    
    db.execute();
    menu.execute();
}