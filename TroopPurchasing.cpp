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
        auto cur3=db.get_statement();
        auto cur4=db.get_statement();
        
        cur1->set_sql("INSERT INTO player_army (player_ID, military_ID, map_ID)"
                      "VALUES (?,?,?)");
        cur1->prepare();
        cur1->bind(1, player_ID);
        cur1->bind(2, troop_ID);
        cur1->bind(3, map_ID);
        
        cur2->set_sql("SELECT cost 
                      "FROM military_Units"
                      "WHERE ID = ?");
        cur2->prepare();
        cur2->bind(1, troop_ID);
        cur2->step();
        
        int cost = cur2->get_int(0);
        
        cur3->set_sql("SELECT total_Money"
                      "FROM player")
        cur3->prepare();
        cur3->step();
        
        int total_Money = cur3->get_int(0);
        total_Money = total_Money - cost
        
        cur4->set_sql("UPDATE player"
                      "SET total_Money = ?")
        cur4->prepare();
        cur4->bind(1, total_Money)
            
        
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}
