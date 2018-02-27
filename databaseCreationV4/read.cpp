#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"

void military_Units(){
    
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM military_Units "); //If you want to see other table replace military_Units with production_Units
        
        cur->prepare();
        cout << "ID " << " Name " << "  Atk " << "Def " << "Cost" << endl; 
        
        while(cur->step()){
            int ID = cur->get_int(0);
            string Name = cur->get_text(1);
            int Attack = cur->get_int(2);
            int Defence = cur->get_int(3);
            int Cost = cur->get_int(4);
            cout << ID << " " << Name << " " << Attack << " " << Defence << " " << Cost << endl;
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void production_Units(){
    
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM production_Units "); //If you want to see other table replace military_Units with production_Units
        
        cur->prepare();
        cout << "ID " << " Name " << "  Income " << "Cost" << endl; 
        
        while(cur->step()){
            int ID = cur->get_int(0);
            string Name = cur->get_text(1);
            int Income = cur->get_int(2);
            int Cost = cur->get_int(3);
            cout << ID << " " << Name << " " << Income << " " << Cost << endl;
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void map(){
    
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM Map "); //If you want to see other table replace military_Units with production_Units
        
        cur->prepare();
        cout << "ID " << " Name " << "  Owned? " << endl; 
        
        while(cur->step()){
            int ID = cur->get_int(0);
            string Name = cur->get_text(1);
            string Owned = cur->get_text(2);
            cout << ID << " " << Name << " " << Owned << endl;
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void saves(){
    
    string sqliteFile = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        
        cur->set_sql( "SELECT * FROM Saves ");
        
        cur->prepare();
        
        while(cur->step()){
            string Name = cur->get_text(0);
            int Atk1 = cur->get_int(1);
            int Def1 = cur->get_int(2);
            int Atk2 = cur->get_int(3);
            int Def2 = cur->get_int(4);
            string Territories = cur->get_text(5);
            cout << Name << "  " << Atk1 << "  " << Def1 << "  " << Atk2 << "  " << Def2 << "  " << Territories << endl;
        }
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
int read(){
    int user_Input;
    while(user_Input == 1||2||3||4||5){
        cout << "What file would you like to read? " << endl;
        cout << "1: Military Units  " << "2: Production Units  " << "3: Map  " << "4: Saves " << "5: Cancel" << endl;
        cout << "Enter here: ";
        cin >> user_Input;
    
        if(user_Input == 1){
            military_Units();
        }
        else if(user_Input==2){
            production_Units();
        }
        else if(user_Input==3){
            map();
        }
        else if(user_Input==4){
            saves();
        }
        else if(user_Input==5){
            break;
        }
        else{
            cout << "Please enter a valid number!" << endl;
            cout << "" << endl;
            break;
        }
    }
}

int main(){
    read();
    return 0;
}