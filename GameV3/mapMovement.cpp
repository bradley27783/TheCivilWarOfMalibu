#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>

using namespace std;

#include "libsqlite.hpp"
#include "mapMovement.h"

void UnitMovement::guiHeader(){
    cout << "\033[2J\033[1;1H";
    cout << "Unit Movement: " << endl << "---------------------------------------" << endl;
}

int UnitMovement::moveto_Check(int player_ID){
    //function that shows map
    int user_Input;
    cout << "Where do you want to move to? " << endl << "1: A" << endl << "2: B" << endl << "3: C" << endl << "4: D" << endl << "5: E" << endl << "6: F" << endl << "7: G" << endl << "8: H" << endl << "9: I" << endl << "10: Exit" << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(user_Input == 10){
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

int UnitMovement::movefrom_Check(int player_ID){
    //function that shows map
    int user_Input;
    cout << "Where do you want to move from? " << endl << "1: A" << endl << "2: B" << endl << "3: C" << endl << "4: D" << endl << "5: E" << endl << "6: F" << endl << "7: G" << endl << "8: H" << endl << "9: I" << endl << "10: Exit" << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(user_Input == 10){
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

int UnitMovement::unitType_Check(int player_ID){
    //function that shows map
    int user_Input;
    cout << "What unit type do you want to move? " << endl << "1: HoloSoldier" << endl << "2: HoloBike" << endl << "3: HoloTank" << endl << "4: HoloXCOM" << endl << "5: Exit" << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(user_Input == 5){
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

}  //Want to make this check the database

int UnitMovement::unitAmount_Check(int unitType, int player_ID, int moveFrom){
    //function that shows map
    int user_Input;
    cout << "How many units do you want to move? " << endl;
    cout << "Enter Here: ";
    cin >> user_Input;
    
    if(user_Input == 0){
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
            
            int total = count - user_Input;
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

int UnitMovement::moveUnits(int unitType, int player_ID, int moveFrom, int moveTo, int unitAmount){
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

void UnitMovement::movement_Menu(int player_ID){  
    while(true){  
        guiHeader();
        int moveTo = moveto_Check(player_ID);
        if(moveTo<10 && moveTo>0){
            guiHeader();
            int moveFrom = movefrom_Check(player_ID);
            if(moveFrom<10 && moveFrom>0){
                guiHeader();
                int unitType = unitType_Check(player_ID);
                if(unitType<5 && unitType>0){
                    guiHeader();
                    int unitAmount = unitAmount_Check(unitType, player_ID, moveFrom);
                    if(unitAmount>0){
                        guiHeader();
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