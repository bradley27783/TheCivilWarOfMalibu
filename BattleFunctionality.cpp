#include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include <vector>
using namespace std;

int playerArmyPosition(int player_ID)
{
    string file = "civilwarofMalibu.db";
    try
    {
        int playerArmyPosition;
        cout << "Which army do you want to attack with? ";
        cin >> playerArmyPosition;
            
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        
        cur1->set_sql("SELECT Owned FROM Map "
                      "WHERE player_ID = ? AND map_ID = ? ");
        cur1->prepare();
        cur1->bind(1, player_ID);
        cur1->bind(2, playerArmyPosition);
        cur1->step();
        
        int owned = cur1->get_int(0);
        if( owned != 1 )
        {
            cout << "You do not own this territory" << endl;
        }
        else
        {
            return playerArmyPosition;
        }
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}

int AIArmyPosition(int player_ID)
{
    string file = "civilwarofMalibu.db";
    try
    {
        int AIArmyPosition;
        cout << "Which area do you want to attack? ";
        cin >> AIArmyPosition;
            
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        
        cur1->set_sql("SELECT Owned FROM Map "
                      "WHERE player_ID = ? AND map_ID = ? ");
        cur1->prepare();
        cur1->bind(1, player_ID);
        cur1->bind(2, AIArmyPosition);
        cur1->step();
        
        int owned = cur1->get_int(0);
        if( owned != 0 )
        {
            cout << "You can not attack this area" << endl;
        }
        else
        {
            return AIArmyPosition;
        }
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}

vector<int> troopCounter(int map_ID, int player_ID, string AIorPlayer) ///Counts the attack and defence of the total amount of units 
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();

        int totalAtk = 0;
        int totalDef = 0;
        
        if (AIorPlayer=="Player")
        {
            cur1->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                          "FROM military_Units "
                          "INNER JOIN player_Army ON military_Units.ID = player_Army.military_ID "
                          "WHERE player_Army.player_ID = ? ");        
            cur1->prepare();
            cur1->bind(1, player_ID);
            while( cur1->step() )
            {
                int attackValue = cur1->get_int(0);
                totalAtk = totalAtk + attackValue;
                int defenceValue = cur1->get_int(1);
                totalDef = defenceValue + totalDef;
            }
            vector<int> Atk_Def = {totalAtk,totalDef};
            return Atk_Def;
            }
        
        else if(AIorPlayer=="AI")
        {
            cur1->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                          "FROM military_Units "
                          "INNER JOIN ai_Army ON military_Units.ID = ai_Army.military_ID "
                          "WHERE ai_Army.player_ID = ? ");        
            cur1->prepare();
            cur1->bind(1, player_ID);
            while( cur1->step() )
            {
                int attackValue = cur1->get_int(0);
                totalAtk = totalAtk + attackValue;
                int defenceValue = cur1->get_int(1);
                totalDef = defenceValue + totalDef;
            }
            vector<int> Atk_Def = {totalAtk,totalDef};
            return Atk_Def;
            }

    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int delTroops(int threshold, int map_ID, int player_ID, int AI_map_ID, string AIorPlayer) ///Deletes the top value in the army database tables until it is under the army threshold
{
    const string file = "civilwarofMalibu.db";
    
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        
        if( AIorPlayer == "AI")
        {
            vector<int> armyValues = troopCounter(map_ID, player_ID,  "Player");
            int attackValue = armyValues[0];
            while(attackValue>threshold)
            {
                cur1->set_sql("DELETE FROM player_Army "
                              "WHERE map_ID = ? AND player_ID = ? "
                              "ORDER BY uniqueunit_id ASC "
                              "LIMIT 1; ");
                 cur1->prepare();
                 cur1->bind(1, map_ID);
                 cur1->bind(2, player_ID);
                 cur1->step();
                 cur1->reset();
                 vector<int> armyValues = troopCounter(map_ID, player_ID, "Player");
                 attackValue = armyValues[0];
            }
        }
        
        else if ( AIorPlayer == "Player")
        {
            vector<int> armyValues = troopCounter(AI_map_ID, player_ID, "AI");
            int attackValue = armyValues[0];
            while(attackValue>threshold)
            {
                cur1->set_sql("DELETE FROM ai_Army "
                              "WHERE map_ID = ? AND player_ID = ? "
                              "ORDER BY uniqueunit_id ASC "
                              "LIMIT 1; ");
                 cur1->prepare();
                 cur1->bind(1, AI_map_ID);
                 cur1->bind(2, player_ID);
                 cur1->step();
                 cur1->reset();
                 vector<int> armyValues = troopCounter(AI_map_ID, player_ID, "AI");
                 attackValue = armyValues[0];
            }
        }
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int battle(int map_ID, int player_ID, int AI_map_ID) ///Calculates the threshold for the loss of troops to be used to delete troops from database
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        auto cur2=db.get_statement();

        vector<int> AI_Army = troopCounter(AI_map_ID, player_ID, "AI");
        int AIAttackTotal = AI_Army[0];
        int AIDefenceTotal = AI_Army[1];
        vector<int> player_Army = troopCounter(map_ID, player_ID, "Player");
        int playerAttackTotal = player_Army[0];
        int playerDefenceTotal = player_Army[1];
        int AIAttack = rand() % AIAttackTotal/10 + AIAttackTotal;
        int AIDefence = rand() % AIDefenceTotal/10 + AIDefenceTotal;
        int playerAttack = rand() % playerAttackTotal/10 + playerAttackTotal;
        int playerDefence = rand() % playerDefenceTotal/10 + playerDefenceTotal;

        cout << "Player Attack roll is: " << playerAttack << endl;
        cout << "AI Attack roll is: " << AIAttack << endl;
        cout << "Player Def roll is: " << playerDefence << endl;
        cout << "AI Def roll is: " << AIDefence << endl;    
        if (AIAttack>playerAttack)
        {
            if (AIAttack>2*playerAttack)
            {
                cout << "AI wiped out your army!" << endl;
                cur1->set_sql("DELETE FROM player_Army "
                              "WHERE map_ID = ? AND player_ID = ? ");
                cur1->prepare();
                cur1->bind(1, map_ID);
                cur1->bind(2, player_ID);
                cur1->step();
                
                cur2->set_sql("UPDATE Map "
                              "SET Owned = 0 "
                              "WHERE map_ID = ? AND player_ID = ? ");
                cur2->prepare();
                cur2->bind(1, map_ID);
                cur2->bind(2, player_ID);
                cur2->step();
                
            }
            else
            {
                cout << "AI won the battle!" << endl;
                int threshold = static_cast<double>(AIAttack) - (static_cast<double>(AIAttack)*(static_cast<double>(AIDefence)/static_cast<double>(playerAttack)));
                delTroops(threshold, map_ID, player_ID, AI_map_ID, "AI");
            }
        }
        else if (playerAttack>AIAttack)
        {
            if (playerAttack>2*AIAttack)
            {
                cout << "You wiped out their army!" << endl;
                cur1->set_sql("DELETE FROM ai_Army "
                              "WHERE map_ID = ? AND player_ID = ? ");
                cur1->prepare();
                cur1->bind(1, AI_map_ID);
                cur1->bind(2, player_ID);
                cur1->step();
                                
                cur2->set_sql("UPDATE Map "
                              "SET Owned = 1 "
                              "WHERE map_ID = ? AND player_ID = ? ");
                cur2->prepare();
                cur2->bind(1, AI_map_ID);
                cur2->bind(2, player_ID);
                cur2->step();
            }
            else
            {
                cout << "You won the battle!" << endl;
                int threshold = static_cast<double>(playerAttack) - (static_cast<double>(playerAttack)*(static_cast<double>(playerDefence)/static_cast<double>(AIAttack)));
                delTroops(threshold, map_ID, player_ID, AI_map_ID, "Player");
            }
        }
        else if (playerAttack==AIAttack)
        {
            cout << "Battle was a draw!" << endl;
        }
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}

main()
{
    int map_ID = playerArmyPosition(player_ID);
    int AI_map_ID = AIArmyPosition(player_ID);
    battle(map_ID, player_ID, AI_map_ID);
}
