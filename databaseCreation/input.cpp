#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"

int main(){
    
    
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO production_Units "
                      "VALUES (?,?,?,?);");

        cur->prepare();
        cur->bind(1,001);   //ID
        cur->bind(2,"HoloSoldier");   //UnitName
        cur->bind(3,10);   //Attack
        cur->bind(4,5);   //Defence
        cur->bind(5,5);   //Cost
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
        return 1;
    }
    return 0;
}