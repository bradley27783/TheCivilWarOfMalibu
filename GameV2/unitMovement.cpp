#include <iostream>
#include <string>
#include "libsqlite.hpp"

using namespace std;

void add(){
    string file = "civilwarofMalibu.db";
    
        try{
            sqlite::sqlite db( file );
            auto cur = db.get_statement();
            auto cur2 = db.get_statement();
            
            cur2->set_sql( "PRAGMA foreign_keys = ON;");
            cur2->prepare();
            cur2->step();

            cur->set_sql( "INSERT INTO player_Army (player_ID, military_ID, map_ID)"
                          "VALUES (1,4,1);");
            cur->prepare();
            
            
            while(cur->step()){
                int playerID = cur->get_int(0);
                int uniqueID = cur->get_int(1);
                int militaryID = cur->get_int(2);
                int mapID = cur->get_int(3);
            cout << playerID << " " << uniqueID <<" " << militaryID<< " " <<mapID <<endl; 
            }
            }
        catch( sqlite::exception e){
            std::cerr << e.what() << endl;
        }
}
void read(){
    string file = "civilwarofMalibu.db";
    
        try{
            sqlite::sqlite db( file );
            auto cur = db.get_statement();

            cur->set_sql( "SELECT * FROM player_Army; ");
            cur->prepare();
            
            
            while(cur->step()){
                int playerID = cur->get_int(0);
                int uniqueID = cur->get_int(1);
                int militaryID = cur->get_int(2);
                int mapID = cur->get_int(3);
            cout << playerID << " " << uniqueID <<" " << militaryID<< " " <<mapID <<endl; 
            }
            }
        catch( sqlite::exception e){
            std::cerr << e.what() << endl;
        }
}

int main(){
    add();
    read();
}