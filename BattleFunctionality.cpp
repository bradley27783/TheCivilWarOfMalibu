#include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include <vector>
using namespace std;

int delTroops(threshold, map_ID, player_ID)
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        
        vector<int> armyValues troopCounter(map_ID, player_ID);
        int attackValue = armyValues[0];
        
        
        while( attackValue > threshold )
        {
            vector<int> armyValues troopCounter(map_ID, player_ID);
            int attackValue = armyValues[0];
            
            cur1->set_sql("DELETE TOP FROM player_Army "
                          "WHERE map_ID = ? AND player_ID = ? ")
            cur1->prepare();
            cur1->bind(1, map_ID);
            cur1->bind(2, player_ID);
            cur1->step();
        }
        
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}

vector<int> troopCounter(map_ID, player_ID)
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        auto cur2=db.get_statement();
        auto cur3=db.get_statement();

        cur1->set_sql("SELECT * "
                      "FROM player_Army "
                      "WHERE  map_ID = ? AND player_ID = ? ");
        cur1->prepare();
        cur1->bind(1, map_ID);
        cur1->bind(2, player_ID);
        
        int totalAtk = 0;
        int totalDef = 0;

        cur2->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                      "FROM military_Units "
                      "INNER JOIN player_Army ON military_Units.ID = player_Army.military_ID ");        
        cur2->prepare();
        
        while( cur2->step() )
        {
            int attackValue = cur2->get_int(0);
            totalAtk = totalAtk + attackValue;
            int defenceValue = cur2->get_int(1);
            totalDef = defenceValue + totalDef;
        }
        vector<int> Atk_Def = {totalAtk,totalDef};
        cout << Atk_Def[0] << " || " << Atk_Def[1] << endl;
        return Atk_Def;
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}

int battle(map_ID, player_ID, AI_map_ID)
{
    vector<int> AI_Army troopCounter(AI_map_ID, player_ID);
    int AIAttackTotal = AI_Army[0];
    int AIDefenceTotal = AI_Army[1];
    vector<int> player_Army troopCounter(map_ID, player_ID);
    int playerAttackTotal = player_Army[0];
    int playerDefenceTotal = player_Army[1];
    
    AIAttack = rand() % AIAttackTotal/10 + AIAttackTotal;
    AIDefence = rand() % AIDefenceTotal/10 + AIDefenceTotal;
    playerAttack = rand() % playerAttackTotal/10 + playerAttackTotal;
    playerDefence = rand() % playerDefenceTotal/10 + playerDefenceTotal;
    
    if (AIAttackTotal>playerAttackTotal)
    {
        if (AIAttackTotal>2*playerAttackTotal)
        {
            cout << "AI wiped out your army!" << endl
        }
        else
        {
            cout << "AI won the battle!" << endl
            
            int threshold = playerAttack - (playerAttack*(playerDefence/AIAttack));
            
        }
    }
    else if (playerAttackTotal>AIAttackTotal)
    {
        if (playerAttackTotal>2*AIAttackTotal)
        {
            cout<< "You wiped out the AI army!" << endl;
            
            
        }
        else
        {
            cout << "You won the battle!" << endl;
            
            
        }
    }
    else
    {
        
    }
}

main()
{
    troopCounter();
}
