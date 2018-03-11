#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;

void amountUnits(int player_ID, int troop_ID)
    int amount
    cout << "How many troops do you want?"
    cin >> amount
    int map_ID
    cout << "Where do you want the units placed?";
    cin >> map_ID
    for(int i=0 : amount+1 : i++)
        purchaseUnitType(player_ID, troop_ID, map_ID)
        
void purchaseUnitType(int player_ID, int troop_ID, int map_ID)
    {
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        auto cur2=db.get_statement();
        
        cur1->set_sql("INSERT INTO player_army (player_ID, military_ID, map_ID)"
                     "VALUES (?,?,?)");
        cur1->bind(1, player_ID);
        cur1->bind(2, troop_ID);
        cur1->bind(3, map_ID);
        
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}
