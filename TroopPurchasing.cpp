#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;

void purchaseUnitType(int player_ID, int troop_ID, int map_ID)
{
    string file = "civilwarofMalibu.db";
    cout << "Test0" << endl;
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        auto cur2=db.get_statement();
        auto cur3=db.get_statement();
        auto cur4=db.get_statement();
        
        cur1->set_sql("INSERT INTO player_Army (player_ID, military_ID, map_ID)"
                      "VALUES (?,?,?);");
        cur1->prepare();
        cur1->bind(1, player_ID);
        cur1->bind(2, troop_ID);
        cur1->bind(3, map_ID); 
        cout << "Test1" << endl; 
        
        
        cur2->set_sql("SELECT *"
                      "FROM military_Units;");
        cur2->prepare();
        cur2->step(); 
        
        int cost = cur2->get_int(4);
        
        cout << "Test2" << endl;
        
        cur3->set_sql("SELECT *"
                      "FROM player;");
        cur3->prepare();
        cur3->step();
        int total_Money = cur2->get_int(4);

        total_Money = total_Money - cost;
        cout << "Test3" << endl;
        
        cur4->set_sql("UPDATE player"
                      "SET total_Money = ?"
                      "WHERE player_ID = ?;");
        cur4->prepare();
        cur4->bind(1, total_Money);
        cur4->bind(2, player_ID);
        cur4->step();
        cout << "Test4" << endl;
            
        
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}



int amountUnits()
{
    int amount;
    cout << "How many troops do you want?";
    cin >> amount;
    return amount;
}

int mapArea(){
    cout << "Where do you want the units placed?";
    int map_ID;
    cin >> map_ID;
    return map_ID;
}

int main()
{
    int player_ID=3;
    int troop_ID=1;
    int amount = amountUnits();
    int map_ID = mapArea();
    int i;
    for(i = 0; i<=amount; i++){
        purchaseUnitType(player_ID, troop_ID, map_ID);
    }
    
    
}
