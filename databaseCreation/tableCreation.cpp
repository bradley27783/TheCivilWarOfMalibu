#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"

int main(){
    
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "CREATE TABLE owned_Territories (ID INTEGER,Name TEXT,Owned BOOLEAN);");
        cur->prepare();
        cur->step();
        
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
        return 1;
    }
    return 0;
}