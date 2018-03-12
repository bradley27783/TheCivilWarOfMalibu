#include <iostream>
#include <string>
//#include <ctype.h>
#include <unistd.h>
#include "libsqlite.hpp"
using namespace std;


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

void purchaseUnitType(int player_ID, int troop_ID, int map_ID)
{
    int amount = amountUnits();   
    int i;
    for(i = 0; i<=amount; i++){
        string file = "civilwarofMalibu.db";
        try
        {
            sqlite::sqlite db(file);
            auto cur1=db.get_statement();
            auto cur2=db.get_statement();
            auto cur3=db.get_statement();
            auto cur4=db.get_statement();

            cur1->set_sql("INSERT INTO player_Army (player_ID, military_ID, map_ID) "
                          "VALUES (?,?,?);");
            cur1->prepare();
            cur1->bind(1, player_ID);
            cur1->bind(2, troop_ID);
            cur1->bind(3, map_ID); 
            cur1->step(); 


            cur2->set_sql("SELECT * "
                          "FROM military_Units "
                          "WHERE ID = ? ");
            cur2->prepare();
            cur2->bind(1, troop_ID);
            cur2->step(); 

            int cost = cur2->get_int(4);

            cur3->set_sql("SELECT * "
                          "FROM player "
                          "WHERE player_ID = ? ;");
            cur3->prepare();
            cur3->bind(1, player_ID);
            cur3->step();
            int total_Money = cur3->get_int(3);
            
            cout << total_Money << endl;
            total_Money = total_Money - cost;
            cout << total_Money << endl;

            if (total_Money < 0)
            {
                break;
            }
            else if(total_Money > 0){
            
            cur4->set_sql("UPDATE player "
                          "SET total_Money = ? "
                          "WHERE player_ID = ? ");
            cur4->prepare();
            cur4->bind(1, total_Money);
            cur4->bind(2, player_ID);
            cur4->step();
            }

        }
        catch(sqlite::exception e)
        {
            std::cerr << e.what() << endl;
        }
    }
}


int main()
{
    int player_ID=4;
    int troop_ID=1;
    int map_ID = mapArea();
    purchaseUnitType(player_ID, troop_ID, map_ID);       
}
