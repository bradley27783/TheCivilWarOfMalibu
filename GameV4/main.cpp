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

int Menu::menu_militaryUnits(int player_ID, int totalMoney){
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM military_Units ");
        
        int user_Input;
        while(true){
            
        cur->prepare();
        cout << "Name" << setfill(' ') << setw(21) << "Atk   " << "Def   " << "Cost" << endl; 
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
            
            if(cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter an integer!" << endl;
                    sleep(1);
                    cout << "\033[2J\033[1;1H";
                    continue;
                }
        
            else if(user_Input == 1){
                cout << "You have purchased a Soldier! " << endl;
                sleep(1);
                //break;
            }
            else if(user_Input == 2){
                cout << "You have purchased a Bike!" << endl;
                sleep(1);
                //break;
            }
            else if(user_Input == 3){
                cout << "You have purchased a Tank!" << endl;
                sleep(1);
                //break;
            }
            else if(user_Input == 4){
                cout << "You have purchased an XCOM!" << endl;
                sleep(1);
                //break;
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
    
int Menu::menu_productionUnits(int player_ID, int totalMoney){
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM production_Units ");
        int user_Input;
        while(true){
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
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter an integer!" << endl;
                    sleep(1);
                    cout << "\033[2J\033[1;1H";
                    continue;
                }       
                else if(user_Input == 1){
                    cout << "You have purchased a Fishing Boat! " << endl;
                    sleep(1);
                    //break;
                }
                else if(user_Input == 2){
                    cout << "You have purchased a Mine!" << endl;
                    sleep(1);
                    //break;
                }
                else if(user_Input == 3){
                    cout << "You have purchased a Oil Platform!" << endl;
                    sleep(1);
                    //break;
                }
                else if(user_Input == 4){
                    break;
                }
            }
        }
        catch( sqlite::exception e){
            std::cerr << e.what() << endl;
        }
}

int Menu::store_Menu(int player_ID, int totalMoney){
    int user_Input;
    while(true){
        cout << "\033[2J\033[1;1H";
        cout << "Store: " << endl << "---------------------------------------" << endl << "1: Military" << endl << "2: Production" << endl << "3: Exit" << endl;
        cout << "What type of unit do you want to buy? Please enter here: ";

        cin >> user_Input;
        cout << "\033[2J\033[1;1H";
        
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter an integer!" << endl;
            sleep(1);
            continue;
        }
        else if(user_Input == 1){
            menu_militaryUnits(player_ID,totalMoney);
        }
        else if(user_Input == 2){
            menu_productionUnits(player_ID,totalMoney);
        }
        if(user_Input == 3){
            break;
        }
    }
}
    
int Menu::main_Menu(int player_ID, int turn,int totalMoney){
    
    UnitMovement move;    
    
    int user_Input;
    
    while(true){
        cout << "\033[2J\033[1;1H";
        cout << "Menu: " << "    " << "HoloCoins: " << totalMoney << "    "<< "Turn: " << turn << endl << "---------------------------------------------" << endl << "1: Map" << endl << "2: Attack" << endl << "3: Move Units" << endl << "4: Store" << endl << "5: Next Turn" << endl << "6: Save" << endl << "7: Exit" << endl;
        cout << "What do you want to do? Please enter here: ";

        cin >> user_Input;
        cout << "\033[2J\033[1;1H";

        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter an integer!" << endl;
            sleep(1);
            continue;
        }    
        else if(user_Input == 1){
            cout << "Map" << endl;
        }
        else if(user_Input == 2){
            cout << "Attack" << endl;
        }
        else if(user_Input == 3){
            move.execute(player_ID);
        }
        else if(user_Input == 4){
            store_Menu(player_ID,totalMoney);
        }
        else if(user_Input == 5){
            cout << "Next turn" << endl;
        }
        else if(user_Input == 6){
            cout << "Save" << endl;
        }
        else if(user_Input == 7){ //Exit
            int user_Input;
            cout << "Are you sure you want to exit?" << endl << "1: Yes" << endl << "2: No" << endl << "Please enter here: ";
            cin >> user_Input;
            if(user_Input == 1){
                cout << "\033[2J\033[1;1H";
                break;
            }
            else if(user_Input == 0){
                continue;
            }
        }
    }
}
/*
int Menu::turn(){
    int turn = playerinfo.get_playerTurns(player_ID); //Fetches the turn count for the player
}*/

int Menu::execute(int player_ID, int turn, int totalMoney){
    main_Menu(player_ID, turn, totalMoney);        
}

int main(){
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
    int turn = playerinfo.get_playerTurns(player_ID); //Fetches the turn count for the player
    int totalMoney = playerinfo.get_playerMoney(player_ID); //Fetches the total amount of HC for the player
    
    if(player_ID != 0){
    Menu menu;
    menu.execute(player_ID, turn, totalMoney);
    }   
}