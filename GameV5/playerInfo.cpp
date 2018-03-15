#include <iostream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <unistd.h>
using namespace std;
#include "libsqlite.hpp"
#include "playerInfo.hpp"

int PlayerInfo::get_playerID(){ //Fetches the players ID
    string File = "civilwarofMalibu.db";
    int player_ID;
    string player_Name;
    int player_Turn;
    
    while(true){
        try{
            sqlite::sqlite db( File );
            auto cur1 = db.get_statement();      //Cur1 creates a dynamic exit clause
            auto cur2 = db.get_statement();      //Cur2 Grabs player_ID, player_Name and player_Turn from the database

            cur1->set_sql("SELECT COUNT(*) FROM player;");

            cur1->prepare();
            cur1->step();
            int count = cur1->get_int(0);
            int exit = count + 1;
            
            cur1->reset();

            cur2->set_sql("SELECT * FROM player;");  //This is to print all accounts to the user

            cur2->prepare();    
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            cout << "    Name        " << "Turns" << endl; 
            cout << "-------------------------------" << endl;
            while(cur2->step()){
                player_ID = cur2->get_int(0);
                string player_Name = cur2->get_text(1);
                player_Turn = cur2->get_int(2);

                cout << player_ID << ": " << setfill(' ') << setw(8) << player_Name << "         " << player_Turn << endl;
            }

            cout << "-------------------------------" << endl;
            cout << exit << ": Exit" << endl;
            cout << "Please select you save: ";
            int user_Input;
            cin >> user_Input;
            if(cin.fail()){ //Checks if cin failed
                cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
                cin.clear(); //Clears the cin
                cin.ignore(10000, '\n'); //Resets the cin
                cout << "Please enter an integer!" << endl;
                sleep(1);
                continue;
            }
            else if(user_Input==exit){
                cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
                return -11513; //Return random return int so we can exit
            }
            else if(user_Input>exit){
                cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
                cout << "Invalid input!" << endl;
                sleep(1);
                continue;
            }
            else{
                cur1->set_sql("SELECT player_ID FROM player " //Grabs players ID and returns it
                              "WHERE player_ID = ? ;");

                cur1->prepare();
                cur1->bind(1,user_Input);
                cur1->step();
                int player_ID = cur1->get_int(0);
                return player_ID;
            }
        }
        catch( sqlite::exception e){
               std::cerr << e.what() << endl;
        }
    }
}

int PlayerInfo::get_playerIncome(int player_ID){
    string File = "civilwarofMalibu.db";
    try{
        sqlite::sqlite db( File );
        auto cur1 = db.get_statement(); 
        
        cur1->set_sql("SELECT COUNT(*) FROM player_Income ;");  //Grabs a count for how many times we have to iterate
        cur1->prepare();
        cur1->step();
        int count = cur1->get_int(0);
        cur1->reset();
        
        cur1->set_sql("SELECT production_Units.Income "
                      "FROM production_Units "
                      "INNER JOIN player_Income ON production_Units.ID = player_Income.unit_ID "
                      "WHERE player_Income.player_ID = ? ; ");   //Joining player_Income with production_Units where the units id is the same and the player_ID is equal to the player 
        cur1->prepare();
        cur1->bind(1,player_ID);
        int i = 0;
        int totalIncome = 10; //Base income Value - Edit this for more or less income per turn -
        for(i; i < count; i++){
            cur1->step();
            int income = cur1->get_int(0);
            totalIncome = income + totalIncome;
        }
        return totalIncome;
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    } 
}

int PlayerInfo::playerCreation(string user_Input){    //This function initialises the players save
    string File = "civilwarofMalibu.db";
        try{
            sqlite::sqlite db( File );
            auto cur1 = db.get_statement(); 
    
            cur1->set_sql("SELECT COUNT(*) FROM player;");
            cur1->prepare();
            cur1->step();
            int player_ID = cur1->get_int(0);
            player_ID = player_ID+1;            
            cur1->reset();
            
            cur1->set_sql("INSERT INTO player(player_ID,player_Name,turn_Count,total_Money)" //Initialise new players save
                          "VALUES(?,?,1,100);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->bind(2,user_Input);
            cur1->step();           
            cur1->reset();
            
            //All the way from START to END is initialising the new players map
            //START
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,1,'A','1',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,2,'B','1',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,3,'C','1',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,4,'D','1',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,5,'E','1',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,6,'F','0',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,7,'G','0',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,8,'H','0',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            cur1->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,9,'I','0',0);");
            cur1->prepare();
            cur1->bind(1,player_ID);
            cur1->step();
            cur1->reset();
            
            //END
        }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    } 
}

string PlayerInfo::create_playerID(){ //This function creates the new users save and will check if the username already exists
    string File = "civilwarofMalibu.db";
    string user_Input;
    while(true){   
        try{
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            cout << "Please enter a username" << endl;
            cout << "1: Exit" << endl;
            cout << "Enter here: ";
            cin >> user_Input;

            sqlite::sqlite db( File );
            auto cur1 = db.get_statement();
            auto cur2 = db.get_statement();

            cur1->set_sql("SELECT COUNT(*) FROM player;"); //Count for how many player there are so we can iterate that amount
            cur1->prepare();
            cur1->step();
            int count = cur1->get_int(0);

            cur2->set_sql("SELECT player_Name FROM player;"); //Grabs all players names from the database
            cur2->prepare();            
            for(count; count!=0; count--){
                cur2->step();
                string name = cur2->get_text(0);

                if(cin.fail()){ //Checks if cin failed
                    cin.clear(); //Clears the cin
                    cin.ignore(10000, '\n'); //Resets the cin
                    cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
                    cout << "Input failed!" << endl;
                    sleep(1);
                    break;
                }
                else if(user_Input=="1"){
                    return "false";
                }
                else if(user_Input==name){
                    cout << "\033[2J\033[1;1H";
                    cout << "Name already Exists. Please enter another Name" << endl;
                    sleep(1);
                    return "false";
                }
                else if((count==1) && (user_Input!=name)){
                    return user_Input;
                }
            }
        }
        catch( sqlite::exception e){
               std::cerr << e.what() << endl;
        }
    }
}

int PlayerInfo::get_playerTurns(int player_ID){ //This function fetches what turn the player is on
    string File = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();

        cur->set_sql( "SELECT turn_Count FROM player "
                      "WHERE player_ID = ?;");

        cur->prepare();
        cur->bind(1, player_ID);

        cur->step();
        int turn = cur->get_int(0);
        return turn;
    }
    catch( sqlite::exception e){
           std::cerr << e.what() << endl;
    }
}

int PlayerInfo::get_playerMoney(int player_ID){ //This function fetches the amount of money the player has
    string File = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();

        cur->set_sql( "SELECT total_Money FROM player "
                      "WHERE player_ID = ?;");

        cur->prepare();
        cur->bind(1, player_ID);

        cur->step();
        int turn = cur->get_int(0);
        return turn;
    }
    catch( sqlite::exception e){
           std::cerr << e.what() << endl;
    }
}

int PlayerInfo::checkPlayer(){
    while(true){
        cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
        cout << "Do you already have a save?" << endl;
        cout << "1: Yes" << endl;
        cout << "2: No" << endl;
        cout << "3: Exit" << endl;
        cout << "Enter Here: ";
        int user_Input;
        cin >> user_Input;
        
        if(cin.fail()){ //Checks if cin failed
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            cout << "Please enter an integer!" << endl;
            cin.clear(); //Clears the cin
            cin.ignore(10000, '\n'); //Resets the cin
            sleep(1);
            continue;
        }
        else if(user_Input==1){
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            return get_playerID();
        }
        else if(user_Input==2){
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            string create = create_playerID();
            if(create=="false"){
                return -1234124; //Returns random int for failed username
            }
            else{
                playerCreation(create);
            }
        }
        else if(user_Input==3){
            cout << "\033[2J\033[1;1H"; //Linux command to clear the terminal
            return 0; //Returns 0 for exit
        }
    }
}