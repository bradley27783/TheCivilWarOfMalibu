#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;

/*void purchaseProduction()
{
    string sqliteFile = "civilwarofMalibu.db";
    
    try                                                 //If its not finished pls help me.
    {
        sqlite::sqlite db(sqliteFile);
        auto cur=db.get_statement();
        
        cur->set_sql("INSERT INTO player_income "
                     "VALUES (?)");
        cur->bind(1);
    }
}*/

int main()
{
    string sqliteFile = "civilwarofMalibu.db";
    
    try
    {
        sqlite::sqlite db(sqliteFile);
        auto cur=db.get_statement();
        
        cur->set_sql("SELECT * "
                     "FROM production_Units ");
        cur->prepare();
        while ( cur->step() )
            cout <<cur->get_int(0)<< " " << cur->get_text(1) << " " <<cur->get_int(2)<< " " << cur->get_int(3) << endl;
    }
    catch( sqlite::exception e)      // catch all sql issues
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
