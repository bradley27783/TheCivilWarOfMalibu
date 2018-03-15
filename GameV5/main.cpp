#include <iostream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <unistd.h>
using namespace std;


#include "libsqlite.hpp"
#include "mapMovement.h"
#include "main.h"
#include "playerInfo.hpp"
#include "TroopPurchasing.hpp"

int Menu::menu_Header(string menu, int player_ID){   //This function creates a header for the gui
    
    PlayerInfo playerinfo; //Creates an object of the class PlayerInfo
    int turn = playerinfo.get_playerTurns(player_ID); //Fetches the turn count for the player
    int totalMoney = playerinfo.get_playerMoney(player_ID); //Fetches the total amount of HC for the player
    int income = playerinfo.get_playerIncome(player_ID);
    
    cout << "\033[2J\033[1;1H";  //Linux command to clear the terminal
    cout << "----------------------------------------------------------------------------" << endl;
    cout << menu <<": " << "  " << "HoloCoins: " << totalMoney << "  "<< "HoloCoins/t: " << income << "   " <<"Turn: " << turn << endl; 
    cout << "----------------------------------------------------------------------------" << endl;
} //Header gui

int Menu::menu_militaryUnits(int player_ID){  //This function displays to the user what military units are availible for purchasing
    TroopPurchasing troopPurchasing; //Creates an object of the class TroopPurchasing - Adams function
    string sqliteFile = "civilwarofMalibu.db";
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM military_Units ");
        
        int user_Input;
            
        cur->prepare();
        cout << "Name" << setfill(' ') << setw(21) << "Atk   " << "Def   " << "Cost" << endl; 
        cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl; 
        
        while(cur->step()){
            int ID = cur->get_int(0);
            string Name = cur->get_text(1);
            int Attack = cur->get_int(2);
            int Defence = cur->get_int(3);
            int Cost = cur->get_int(4); 
            Name.append(16 - Name.length(),' ');
            
            cout << ID << ": " << Name << setfill(' ') << setw(4) << Attack << setfill(' ') << setw(6) << Defence << setfill(' ') << setw(7) << Cost << endl;
        }
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << "5: Exit to menu" << endl;
            cout << "What would you like to purchase? ";
            cin >> user_Input;
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            
            if(cin.fail()){ //Checks if the cin failed
                    cin.clear(); //Clears the cin
                    cin.ignore(10000, '\n'); //Resets the cin
                    cout << "Please enter an integer!" << endl;
                    sleep(1);
                }
        
            else if(user_Input == 1){ //HoloSoldier
                troopPurchasing.execute(player_ID, user_Input); //- Adams function
            }
            else if(user_Input == 2){ //HoloBike
                troopPurchasing.execute(player_ID, user_Input); //- Adams function
            }
            else if(user_Input == 3){ //HoloTank
                troopPurchasing.execute(player_ID, user_Input); //- Adams function
            }
            else if(user_Input == 4){ //HoloXCOM
                troopPurchasing.execute(player_ID, user_Input); //- Adams function
            }
            else if(user_Input == 5){ //Exit
                return 5;
            }
    }      
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
} //Military units store
    
int Menu::menu_productionUnits(int player_ID){ //This function displays to the user what production units are availible for purchasing
    string sqliteFile = "civilwarofMalibu.db";
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM production_Units ");
        int user_Input;
        cur->prepare();
        cout << "Name" << setfill(' ') << setw(24) << "Income   " << "Cost   " << endl; 
        cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl; 

        while(cur->step()){
            int ID = cur->get_int(0);
            string Name = cur->get_text(1);
            int Income = cur->get_int(2);
            int Cost = cur->get_int(3);
            Name.append(16 - Name.length(),' ');

            cout << ID << ": " << Name << setfill(' ') << setw(6) << Income << setfill(' ') << setw(7) << Cost << endl;
            }
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << "4: Exit to menu" << endl;
            cout << "What would you like to purchase? ";
            cin >> user_Input;
            cout << "\033[2J\033[1;1H";
            if(cin.fail()){ //Checks if cin fail
                cin.clear(); //Clears the cin
                cin.ignore(10000, '\n'); //Resets the cin
                cout << "Please enter an integer!" << endl;
                sleep(1);
            }       
            else if(user_Input == 1){ //HoloBoat
                cout << "You have purchased a Fishing Boat! " << endl;
                sleep(1);
            }
            else if(user_Input == 2){ //HoloBoat
                cout << "You have purchased a Mine!" << endl;
                sleep(1);
            }
            else if(user_Input == 3){ //HoloBoat
                cout << "You have purchased a Oil Platform!" << endl;
                sleep(1);
            }
            else if(user_Input == 4){ //Exit
                return 4;
            }
        }
        catch( sqlite::exception e){
            std::cerr << e.what() << endl;
        }
} //Production units store

int Menu::store_Menu(int player_ID){ //The function is the menu for the store so the user can select military or production units.
    int user_Input;
    string menu = "Store";
    menu_Header(menu,player_ID);
    cout << "1: Military" << endl << "2: Production" << endl << "3: Exit" << endl;
    cout << "What type of unit do you want to buy? Please enter here: ";

    cin >> user_Input;

    if(cin.fail()){ //Checks if the cin failed and if it did, send a message to the user and reset
        cin.clear(); //Clears the cin
        cin.ignore(10000, '\n'); //Resets the cin
        cout << "Please enter an integer!" << endl;
        sleep(1);
    }
    else if(user_Input == 1){ //Run the military store
        int military_Units;
        while(military_Units != 5){
            string menu = "Military Menu";
            menu_Header(menu,player_ID);
            military_Units = menu_militaryUnits(player_ID);
        }
    }
    else if(user_Input == 2){ //Run the production store
        int production_Units; 
        while(production_Units != 4){
            string menu = "Production Menu";
            menu_Header(menu,player_ID);
            production_Units = menu_productionUnits(player_ID);
        }
    }
    if(user_Input == 3){
        return 3;
    }
} //Store menu
    
int Menu::main_Menu(int player_ID){ //Main body of the game
    
    UnitMovement move;
    PlayerInfo playerinfo;
    
    int user_Input;
         
    string menu = "Main Menu";
    menu_Header(menu,player_ID);

    cout << "1: Map" << endl << "2: Attack" << endl << "3: Move Units" << endl << "4: Store" << endl << "5: Next Turn" << endl << "6: Exit" << endl;
    cout << "What do you want to do? Please enter here: ";

    cin >> user_Input;

    if(cin.fail()){ //Checks if the cin has failed
        cin.clear(); //Clears the cin
        cin.ignore(10000, '\n'); //Resets the cin
        cout << "Please enter an integer!" << endl;
        sleep(1);
    }    
    else if(user_Input == 1){ //Shows the map
        cout << "Map" << endl;
    }
    else if(user_Input == 2){ //Runs attack
        cout << "Attack" << endl;
    }
    else if(user_Input == 3){ //Move units
        move.execute(player_ID);
    }
    else if(user_Input == 4){ //Show store menu
        int storeMenu;
        while(storeMenu != 3){
            storeMenu = store_Menu(player_ID);
        }
    }
    else if(user_Input == 5){ //Next turn
        next_Turn(player_ID);
    }
    else if(user_Input == 6){ //Exit
        int user_Input;
        string menu = "Exit";
        menu_Header(menu,player_ID);
        cout << "Are you sure you want to exit?" << endl;  //Double checks that the player wants to quit
        cout << "1: Yes" << endl;
        cout << "2: No" << endl;
        cout << "Please enter here: ";
        cin >> user_Input;
        if(user_Input == 1){ //Ends the game
            cout << "\033[2J\033[1;1H"; //Linux command to clear terminal
            return 1;
        }
    }
} //Main menu

void Menu::next_Turn(int player_ID){
    PlayerInfo playerinfo; //Create an object of the class PlayerInfo
    int turn = playerinfo.get_playerTurns(player_ID);
    int income = playerinfo.get_playerIncome(player_ID);
    int totalMoney = playerinfo.get_playerMoney(player_ID);

    totalMoney = totalMoney + income;
    turn = turn + 1;
    
    string File = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();

        cur->set_sql( "UPDATE player "
                      "SET turn_Count = ? "
                      "WHERE player_ID = ? ;");

        cur->prepare();
        cur->bind(1, turn);
        cur->bind(2, player_ID);
        cur->step();
        cur->reset();
        
        cur->set_sql( "UPDATE player "
                      "SET total_Money = ? "
                      "WHERE player_ID = ? ;");

        cur->prepare();
        cur->bind(1, totalMoney);
        cur->bind(2, player_ID);
        cur->step();
    }
    catch( sqlite::exception e){
           std::cerr << e.what() << endl;
    }
}

int Menu::execute(int player_ID){ //Execute / runs the game
    int mainMenu;
    while(mainMenu != 1){
        mainMenu = main_Menu(player_ID); //Runs the Menu/Game
    }
} //Execute / runs the game

int main(){ //Fetches the player id and executes the game
    PlayerInfo playerinfo;
    int player_ID;
    while(true){
        player_ID = playerinfo.checkPlayer();
        if(player_ID >= 0){
            break;
        }
        else{
            continue;
        }
    }
    
    if(player_ID != 0){
    Menu menu;
    menu.execute(player_ID);
    }   
}