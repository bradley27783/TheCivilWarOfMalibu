#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;

int main()
{
    int a;
    string sqliteFile = "civilwarofMalibu.db";
    
    try
    {
        sqlite::sqlite db(sqliteFile);
        auto cur=db.get_statement();
        
        cur->set_sql("SELECT * "
                     "FROM production_Units ");
        cur->prepare();
        cout << "              " << "Income  /  Cost " << endl;
        while ( cur->step() )
            cout << cur->get_int(0) << " " << cur->get_text(1) << "   " <<cur->get_int(2)<< "   " << cur->get_int(3) << endl;
    }
    catch( sqlite::exception e)      // catch all sql issues
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    if( a == 1 )
    {
        cout << "How many would you like to buy? " << endl;
        int b;
        cin >> b;
    
        try                                                 
        {
            sqlite::sqlite db(sqliteFile);
            auto cur=db.get_statement();
        
            cur->set_sql("INSERT INTO player_income "
                         "VALUES (?)");
            cur->prepare();
            cur->bind(1,b);
            cur->step();
            
            catch( sqlite::exception e )
            {
                cerr << e.what() << endl;
                return 1;
            }
        }
    }
        
    else if( a == 2 )
    {
        cout << "How many would you like to buy? " << endl;
        int b;
        cin >> b;
    
        try                                                 
        {
            sqlite::sqlite db(sqliteFile);
            auto cur=db.get_statement();
        
            cur->set_sql("INSERT INTO player_income "
                         "VALUES (?)");
            cur->prepare();
            cur->bind(1,b);
            cur->step();

            catch( sqlite::exception e )
            {
                cerr << e.what() << endl;
                return 1;
            }
        }
    }
    
    else if( a == 3 )
    {
        cout << "How many would you like to buy? " << endl;
        int b;
        cin >> b;
    
        try                                                 
        {
            sqlite::sqlite db(sqliteFile);
            auto cur=db.get_statement();
        
            cur->set_sql("INSERT INTO player_income "
                         "VALUES (?)");
            cur->prepare();
            cur->bind(1,b);
            cur->step();

            catch( sqlite::exception e )
            {
                cerr << e.what() << endl;
                return 1;
            }
        }
    }
    
    return 0;
}
