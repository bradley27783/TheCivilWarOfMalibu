#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>

using namespace std;

#include "libsqlite.hpp"
#include "mapMovement.h"
#include "main.h"
#include "playerInfo.hpp"

int UnitMovement::check_ownedAmount(int player_ID){ //Checks what part of the map is owned and returns the amount as count
    
    string File = "civilwarofMalibu.db";
    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();

        cur->set_sql("SELECT COUNT(*) FROM Map "
                     "WHERE Owned = ?"
                     "AND player_ID = ?");

        cur->prepare();
        cur->bind(1, 1);
        cur->bind(2, player_ID);

        cur->step();
        int count = cur->get_int(0);
        return count;
    }
    catch( sqlite::exception e){
                   std::cerr << e.what() << endl;
        }
}

void UnitMovement::guiunitAmount(int player_ID){ //Prints the areas owned to the player
    string File = "civilwarofMalibu.db";
    int i;
    int map_ID = 1;
    int map_Owned = check_ownedAmount(player_ID); //Uses the function to get the count to know how many times to loop and what to print
    string area;
    for(map_ID; map_ID<=map_Owned; map_ID++){
        
        //cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
        //cout << map_ID << ": " << "Area " << area << endl << "Unit Type:" <<  " Amount" << endl;
        //cout << "" << endl;
        
        if(map_ID==1){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area A" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        
        else if(map_ID==2){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area B" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);            
        }
        else if(map_ID==3){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area C" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        else if(map_ID==4){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area D" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        else if(map_ID==5){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area E" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        else if(map_ID==6){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area F" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        else if(map_ID==7){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area G" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        else if(map_ID==8){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area H" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
        else if(map_ID==9){
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
            cout << map_ID << ": " << "Area I" << endl << "Unit Type:" <<  " Amount" << endl;
            cout << "" << endl;
            guiunitAmountUnit(player_ID,map_ID);
        }
    }
}

void UnitMovement::guiunitAmountUnit(int player_ID, int map_ID){ //Prints each amount of units in each section of the map
    int i;
    string File = "civilwarofMalibu.db";
    for( i = 1; i<=4; i++){
        try{
            sqlite::sqlite db( File );
            auto cur = db.get_statement();

            cur->set_sql( "SELECT COUNT(*) FROM player_Army "
                          "WHERE military_ID = ?" 
                          "AND player_ID = ?"
                          "AND map_ID = ?;");

            cur->prepare();
            cur->bind(1, i);
            cur->bind(2, player_ID);
            cur->bind(3, map_ID);

            cur->step();
            int count = cur->get_int(0);

            if(i==1){
                cout << "HoloSoldier: " << count << endl;
            }
            else if(i==2){
                cout << "HoloBike: " << count << endl;
            }
            else if(i==3){
                cout << "HoloTank: " << count << endl;
            }
            else if(i==4){
                cout << "HoloXCOM: " << count << endl;
            }
        }
        catch( sqlite::exception e){
               std::cerr << e.what() << endl;

        }
    }
}

int UnitMovement::moveto_Check(int player_ID){ //Checks if the player owns that part of the map where they want to move to

    guiunitAmount(player_ID);
    
    int user_Input;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "10: Exit" << endl;
    cout << "Where do you want to move to? " << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter an integer!" << endl;
        sleep(1);
        cout << "\033[2J\033[1;1H";
    }
    
    else if(user_Input == 10){
        return 10;
    }
    else if(user_Input>10){
        cout << "Invalid Input!" << endl;
        sleep(1);
        return 65380;
    }
    else{
        string File = "civilwarofMalibu.db";

        try{
            sqlite::sqlite db( File );
            auto cur = db.get_statement();

            cur->set_sql( "SELECT map_ID, Owned FROM Map "
                           "WHERE map_ID = ? AND player_ID = ?;");

            cur->prepare();
            cur->bind(1, user_Input);
            cur->bind(2, player_ID);

            cur->step();
            int map_ID = cur->get_int(0);
            string Owned = cur->get_text(1);

            if(Owned=="1"){
                return map_ID;
            }
            else{
                cout << "You don't own that!" << endl;
                sleep(1);
                return 65380;
            }

            }
        catch( sqlite::exception e){
               std::cerr << e.what() << endl;

            }
    }
}

int UnitMovement::movefrom_Check(int player_ID){ //Checks if the player owns that part of the map where they want to move from
    guiunitAmount(player_ID);
    int user_Input;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "10: Exit" << endl;
    cout << "Where do you want to move from? " << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter an integer!" << endl;
        sleep(1);
        cout << "\033[2J\033[1;1H";
    }
    
    else if(user_Input == 10){
        return 10;
    }
    else if(user_Input>10){
        cout << "Invalid Input!" << endl;
        sleep(1);
        return 65380;
    }
    else{
        string File = "civilwarofMalibu.db";

        try{
            sqlite::sqlite db( File );
            auto cur = db.get_statement();

            cur->set_sql( "SELECT map_ID, Owned FROM Map "
                           "WHERE map_ID = ? AND player_ID = ?;");

            cur->prepare();
            cur->bind(1, user_Input);
            cur->bind(2, player_ID);

            cur->step();
            int map_ID = cur->get_int(0);
            string Owned = cur->get_text(1);

            cout << map_ID << "  " << Owned << endl;

            if(Owned=="1"){
                return map_ID;
            }
            else{
                cout << "You don't own that!" << endl;
                sleep(1);
                return 65380;
            }

            }
        catch( sqlite::exception e){
               std::cerr << e.what() << endl;

            }
    }
}

int UnitMovement::unitType_Check(int player_ID){ //Checks if the unit type the user wanted is a valid value
    
    guiunitAmount(player_ID);
    
    int user_Input;
    cout << "---------------------------------------" << endl;
    cout << "What unit type do you want to move? " << endl << "1: HoloSoldier" << endl << "2: HoloBike" << endl << "3: HoloTank" << endl << "4: HoloXCOM" << endl << "5: Exit" << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(cin.fail()){ //Checks if the cin has failed
        cin.clear(); //Clears the cin
        cin.ignore(10000, '\n'); //Resets the cin
        cout << "Please enter an integer!" << endl;
        sleep(1);
        cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
    }
    
    else if(user_Input == 5){ //Exit
        return 5;
    }
    else if(user_Input>5){
        cout << "Invalid Input!" << endl;
        sleep(1);
        return 65380;
    }
    else{
        return user_Input;
    }

}  //Want to make this check the database if I get time

int UnitMovement::unitAmount_Check(int unitType, int player_ID, int moveFrom){
    
    guiunitAmount(player_ID);
    
    while(true){
        int user_Input;
        cout << "---------------------------------------" << endl;
        cout << "How many units do you want to move? " << endl;
        cout << "Enter Here: ";
        cin >> user_Input;

        if(cin.fail()){ //Checks if the cin failed
            cin.clear(); //Clears the cin
            cin.ignore(10000, '\n'); //Resets the cin
            cout << "Please enter an integer!" << endl;
            sleep(1);
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            continue;
        }

        else if(user_Input == 0){
            return 0;
        }
        else if(user_Input<0){
            cout << "Invalid Input!" << endl;
            sleep(1);
            return 65380;
        }
        else{
            string File = "civilwarofMalibu.db";

            try{
                sqlite::sqlite db( File );
                auto cur = db.get_statement();

                cur->set_sql( "SELECT COUNT(*) FROM player_Army "
                              "WHERE map_ID = ? AND player_ID = ? AND military_ID = ?;");

                cur->prepare();
                cur->bind(1, moveFrom);
                cur->bind(2, player_ID);
                cur->bind(3, unitType);

                cur->step();
                int count = cur->get_int(0);

                int total = count - user_Input; //Checks if they have enough units of that type to move
                if(total>=0){
                    return user_Input;
                }
                else{
                    cout << "Insufficient Amount of Units!" << endl;
                    sleep(1);
                    return -65380;
                }

                }
            catch( sqlite::exception e){
                   std::cerr << e.what() << endl;
                }
        }
    }
}

int UnitMovement::moveUnits(int unitType, int player_ID, int moveFrom, int moveTo, int unitAmount){ //Moves the units
    string File = "civilwarofMalibu.db";
        //cur1 determines how many times we have to loop to update the map column
        //cur2 updates the map_ID column from where the units were to the new location
        try{
            sqlite::sqlite db( File );
            auto cur1 = db.get_statement();

            cur1->set_sql( "SELECT uniqueunit_ID FROM player_Army "
                           "WHERE map_ID = ?" 
                           "AND player_ID = ?"
                           "AND military_ID = ?");

            cur1->prepare();
            cur1->bind(1, moveFrom);
            cur1->bind(2, player_ID);
            cur1->bind(3, unitType);
            
            int count = unitAmount;
            
            for(count; count!=0;count--){
                cur1->step();
                int uniqueunit_ID = cur1->get_int(0);
                
                cout << count << endl;
                auto cur2 = db.get_statement();

                cur2->set_sql( "UPDATE player_Army "
                               "SET map_ID = ?"
                               "WHERE map_ID = ?" 
                               "AND player_ID = ?"
                               "AND military_ID = ?"
                               "AND uniqueunit_ID = ?");

                cur2->prepare();
                cur2->bind(1, moveTo);
                cur2->bind(2, moveFrom);
                cur2->bind(3, player_ID);
                cur2->bind(4, unitType);
                cur2->bind(5, uniqueunit_ID);

                cur2->step();
            }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
        }
}

void UnitMovement::movement_Menu(int player_ID){  //Menu to ensure everything flows correctly
    PlayerInfo playerinfo;
    Menu menu;
    
    int turn = playerinfo.get_playerTurns(player_ID); //Fetches the turn count for the player
    int totalMoney = playerinfo.get_playerMoney(player_ID); //Fetches the total amount of HC for the player 
    
    while(true){  
        menu.menu_Header("Move To",player_ID);
        int moveTo = moveto_Check(player_ID);
        if(moveTo<10 && moveTo>0){
            menu.menu_Header("Move From",player_ID);
            int moveFrom = movefrom_Check(player_ID);
            if(moveFrom<10 && moveFrom>0){
                menu.menu_Header("Unit Type",player_ID);
                int unitType = unitType_Check(player_ID);
                if(unitType<5 && unitType>0){
                    menu.menu_Header("Unit Amount",player_ID);
                    int unitAmount = unitAmount_Check(unitType, player_ID, moveFrom);
                    if(unitAmount>0){
                        menu.menu_Header("Moving Units",player_ID);
                        moveUnits(unitType, player_ID, moveFrom, moveTo, unitAmount);
                    }
                    else if(unitAmount==0){
                        break;
                    }
                    else{
                        continue;
                    }
                }
                else if(unitType==5){
                    break;
                }
                else{
                    continue;
                }
            }
            else if(moveFrom==10){
                    break;
                }
            else{
                continue;
            }
        }
        else if(moveTo==10){
                    break;
                }
        else{
            continue;
        }
    }
}

int UnitMovement::execute(int player_ID){    
    movement_Menu(player_ID);
}