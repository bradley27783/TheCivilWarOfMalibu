#include <iostream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <unistd.h>
using namespace std;
#include "libsqlite.hpp"
#include "playerInfo.hpp"

int PlayerInfo::get_playerID(){
    string File = "civilwarofMalibu.db";
    int player_ID;
    string player_Name;
    int player_Turn;
    
    while(true){
        try{
            sqlite::sqlite db( File );
            auto cur1 = db.get_statement();      //Cur1 creates a dynamic exit clause
            auto cur2 = db.get_statement();
            auto cur3 = db.get_statement();

            cur1->set_sql("SELECT COUNT(*) FROM player;");

            cur1->prepare();
            cur1->step();
            int count = cur1->get_int(0);
            int exit = count + 1;

            cur2->set_sql("SELECT * FROM player;");

            cur2->prepare();    
            cout << "\033[2J\033[1;1H";
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
            if(cin.fail()){
                cout << "\033[2J\033[1;1H";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter an integer!" << endl;
                sleep(1);
                continue;
            }
            else if(user_Input==exit){
                cout << "\033[2J\033[1;1H";
                return -11513;
            }
            else if(user_Input>exit){
                cout << "\033[2J\033[1;1H";
                cout << "Invalid input!" << endl;
                sleep(1);
                continue;
            }
            else{

                cur3->set_sql( "SELECT player_ID FROM player "
                               "WHERE player_ID = ?;");

                cur3->prepare();
                cur3->bind(1, user_Input);

                cur3->step();
                int player_ID = cur3->get_int(0);
                return player_ID;
            }
        }
        catch( sqlite::exception e){
               std::cerr << e.what() << endl;
        }
    }
}

int PlayerInfo::playerCreation(string user_Input){    
    string File = "civilwarofMalibu.db";
        try{
            sqlite::sqlite db( File );
            auto cur1 = db.get_statement(); 
            auto cur2 = db.get_statement();
            auto cur3 = db.get_statement(); 
            auto cur4 = db.get_statement();
            auto cur5 = db.get_statement(); 
            auto cur6 = db.get_statement(); 
            auto cur7 = db.get_statement(); 
            auto cur8 = db.get_statement(); 
            auto cur9 = db.get_statement(); 
            auto cur10 = db.get_statement(); 
            auto cur11 = db.get_statement(); 
    
            cur1->set_sql("SELECT COUNT(*) FROM player;");
            cur1->prepare();
            cur1->step();
            int player_ID = cur1->get_int(0);
            player_ID = player_ID+1;
            
            cur2->set_sql("INSERT INTO player(player_ID,player_Name,turn_Count,total_Money)"
                          "VALUES(?,?,1,100);");
            cur2->prepare();
            cur2->bind(1,player_ID);
            cur2->bind(2,user_Input);
            cur2->step();
                
            cur3->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,1,'A','1',0);");
            cur3->prepare();
            cur3->bind(1,player_ID);
            cur3->step();
            
            cur4->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,2,'B','1',0);");
            cur4->prepare();
            cur4->bind(1,player_ID);
            cur4->step();
            
            cur5->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,3,'C','1',0);");
            cur5->prepare();
            cur5->bind(1,player_ID);
            cur5->step();
            
            cur6->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,4,'D','1',0);");
            cur6->prepare();
            cur6->bind(1,player_ID);
            cur6->step();
            
            cur7->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,5,'E','1',0);");
            cur7->prepare();
            cur7->bind(1,player_ID);
            cur7->step();
            
            cur8->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,6,'F','0',0);");
            cur8->prepare();
            cur8->bind(1,player_ID);
            cur8->step();
            
            cur9->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,7,'G','0',0);");
            cur9->prepare();
            cur9->bind(1,player_ID);
            cur9->step();
            
            cur10->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,8,'H','0',0);");
            cur10->prepare();
            cur10->bind(1,player_ID);
            cur10->step();
            
            cur11->set_sql("INSERT INTO Map(player_ID,map_ID,map_Name,Owned,Income)"
                          "VALUES(?,9,'I','0',0);");
            cur11->prepare();
            cur11->bind(1,player_ID);
            cur11->step();
        }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
        sleep(3);
    } 
}

string PlayerInfo::create_playerID(){
    string File = "civilwarofMalibu.db";
    string user_Input;
    while(true){   
        try{
            cout << "\033[2J\033[1;1H";
            cout << "Please enter a username" << endl;
            cout << "1: Exit" << endl;
            cout << "Enter here: ";
            cin >> user_Input;

            sqlite::sqlite db( File );
            auto cur1 = db.get_statement();
            auto cur2 = db.get_statement();

            cur1->set_sql("SELECT COUNT(*) FROM player;");
            cur1->prepare();
            cur1->step();
            int count = cur1->get_int(0);

            cur2->set_sql("SELECT player_Name FROM player;");
            cur2->prepare();            
            for(count; count!=0; count--){
                cur2->step();
                string name = cur2->get_text(0);

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\033[2J\033[1;1H";
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

int PlayerInfo::get_playerTurns(int player_ID){
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

int PlayerInfo::get_playerMoney(int player_ID){
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
        cout << "\033[2J\033[1;1H";
        cout << "Have you played before?" << endl;
        cout << "1: Yes" << endl;
        cout << "2: No" << endl;
        cout << "3: Exit" << endl;
        cout << "Enter Here: ";
        int user_Input;
        cin >> user_Input;
        
        if(cin.fail()){
            cout << "\033[2J\033[1;1H";
            cout << "Please enter an integer!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            sleep(1);
            continue;
        }
        else if(user_Input==1){
            cout << "\033[2J\033[1;1H";
            return get_playerID();
        }
        else if(user_Input==2){
            cout << "\033[2J\033[1;1H";
            string create = create_playerID();
            if(create=="false"){
                return -1234124;
            }
            else{
                playerCreation(create);
            }
        }
        else if(user_Input==3){
            cout << "\033[2J\033[1;1H";
            return 0;
        }
    }
}