#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"

int main(){
    
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
        return 1;
    }
    return 0;
}