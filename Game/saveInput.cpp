#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "libsqlite.hpp"

class saveFile{
    public:
    /* NOT WORKING CURRENTLY
        void checkSave(){
            string file = "civilwarofMalibu.db";
            
            string user_Input;
            cout << "Name your save file: ";
            cin >> user_Input;
            
            try{
                sqlite::sqlite db( file );
                auto cur = db.get_statement();
        
                cur->set_sql( "SELECT Name FROM Saves"); 
                              //"WHERE Name = ?;");

                cur->prepare();
                cur->bind(1, user_Input);
                while(cur->step()){
                    string Name = cur->get_text(0);
                    cout << Name << endl;
                }
            }
            catch( sqlite::exception e){
                std::cerr << e.what() << endl;
            }   */
        }  
        void createSave(int army1totalAttack,int army1totalDefence,int army2totalAttack,int army2totalDefence,string territoryVector){
            string file = "civilwarofMalibu.db";
            cout << army1totalAttack << " " << army1totalDefence << " " << army2totalAttack << " " << army2totalDefence << endl; 
            string user_Input;
            cout << "Name your save file: ";
            cin >> user_Input;
            
            try{
                sqlite::sqlite db( file );
                auto cur = db.get_statement();
        
                cur->set_sql( "INSERT INTO Saves(Name ,Attack1 ,Defence1,Attack2 ,Defence2 ,Territories )"
                              "VALUES (?,?,?,?,?,?);");

                cur->prepare();
                cur->bind(1,user_Input);
                cur->bind(2,army1totalAttack);
                cur->bind(3,army1totalDefence);
                cur->bind(4,army2totalAttack);
                cur->bind(5,army2totalDefence);
                cur->bind(6,territoryVector);
                cur->step();
            }
            catch( sqlite::exception e){
                std::cerr << e.what() << endl;
            }
        }
};


int main(){
    
    saveFile save;
    save.createSave(100,52,200,144,"not working yet so this is a string");
    //save.checkSave();
    return 1;
} 