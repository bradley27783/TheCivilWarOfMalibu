#include <iostream>
#include <string>

using namespace std;

#include "libsqlite.hpp"

void players_Army(){
    string File = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT Owned, Soldiers FROM Map; "); 
                     // "WHERE Owned = ?;");
        
        cur->prepare();
        //cur->bind(1,"1");
        while(cur->step()){
            string Owned = cur->get_text(0);
            int Soldiers = cur->get_int(1);
            cout << Owned << " " << Soldiers << endl;
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void move_Soldiers(){
    string File = "civilwarofMalibu.db";
    
    cout << "Move units to: ";
    int move_Input;
    cin >> move_Input;
    cout << "How many units? ";
    int units_Input;
    cin >> units_Input;
    
    try{
        sqlite::sqlite db( File );
        auto cur = db.get_statement();
        
        cur->set_sql( "UPDATE Map "
                      "SET Soldiers = ? WHERE Owned = '1' AND ID = ?");
        
        cur->prepare();
        cur->bind(1,units_Input);
        cur->bind(2,move_Input);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}


int main(){
    players_Army();
    move_Soldiers();
}