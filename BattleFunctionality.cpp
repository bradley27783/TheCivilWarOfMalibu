#include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include <vector>
using namespace std;

vector<int> troopCounter(int map_ID, int player_ID, string AIorPlayer) ///Counts the attack and defence of the total amount of units 
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();

        cout << "TroopTest1" << endl;
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
            cout << "TroopTest2" << endl;
            while( cur1->step() )
            {
                int attackValue = cur1->get_int(0);
                totalAtk = totalAtk + attackValue;
                int defenceValue = cur1->get_int(1);
                totalDef = defenceValue + totalDef;
            }
            vector<int> Atk_Def = {totalAtk,totalDef};
            cout << Atk_Def[0] << " || " << Atk_Def[1] << endl;
            return Atk_Def;
            }
        
        else if(AIorPlayer=="AI")
        {
            cur1->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                          "FROM military_Units "
                          "INNER JOIN AI_Army ON military_Units.ID = AI_Army.military_ID "
                          "WHERE AI_Army.player_ID = ? ");        
            cur1->prepare();
            cur1->bind(1, player_ID);
            cout << "TroopTest2" << endl;
            while( cur1->step() )
            {
                int attackValue = cur1->get_int(0);
                totalAtk = totalAtk + attackValue;
                int defenceValue = cur1->get_int(1);
                totalDef = defenceValue + totalDef;
            }
            vector<int> Atk_Def = {totalAtk,totalDef};
            cout << Atk_Def[0] << " || " << Atk_Def[1] << endl;
            return Atk_Def;
            }

    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int delTroops(int threshold, int map_ID, int player_ID, string AIorPlayer) ///Deletes the top value in the army database tables until it is under the army threshold
{
    const string file = "civilwarofMalibu.db";
    
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        
        cout << "TestDelete1" << endl;
        
        if( AIorPlayer == "AI")
        {
            vector<int> armyValues = troopCounter(map_ID, player_ID, "Player");
            int attackValue = armyValues[0];
            cout << attackValue << " !!!!!!! " << threshold << endl;
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
                 cout << "DoneBattleAI " << "Threshold: " << threshold << endl;
                 vector<int> armyValues = troopCounter(map_ID, player_ID, "Player");
                 attackValue = armyValues[0];
            }
        }

        else if ( AIorPlayer == "Player")
        {
            vector<int> armyValues = troopCounter(map_ID, player_ID, "AI");
            int attackValue = armyValues[0];
            cout << attackValue << " !!!!!!! " << threshold << endl;
            while(attackValue>threshold)
            {
                cur1->set_sql("DELETE FROM AI_Army "
                              "WHERE map_ID = ? AND player_ID = ? "
                              "ORDER BY uniqueunit_id ASC "
                              "LIMIT 1; ");
                 cur1->prepare();
                 cur1->bind(1, map_ID);
                 cur1->bind(2, player_ID);
                 cur1->step();
                 cur1->reset();
                 cout << "DoneBattleAI " << "Threshold: " << threshold << endl;
                 vector<int> armyValues = troopCounter(map_ID, player_ID, "AI");
                 attackValue = armyValues[0];
            }
        }
        
        cout << "done" << endl << flush;
        
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int battle(int map_ID, int player_ID, int AI_map_ID) ///Calculates the threshold for the loss of troops to be used to delete troops from database
{
    vector<int> AI_Army = troopCounter(AI_map_ID, player_ID, "AI");
    int AIAttackTotal = AI_Army[0];
    int AIDefenceTotal = AI_Army[1];
    vector<int> player_Army = troopCounter(map_ID, player_ID, "Player");
    int playerAttackTotal = player_Army[0];
    int playerDefenceTotal = player_Army[1];
    cout << "testBattle1" << endl;
    int AIAttack = rand() % AIAttackTotal/10 + AIAttackTotal;
    int AIDefence = rand() % AIDefenceTotal/10 + AIDefenceTotal;
    int playerAttack = rand() % playerAttackTotal/10 + playerAttackTotal;
    int playerDefence = rand() % playerDefenceTotal/10 + playerDefenceTotal;
    
    cout << "Player Attack roll is: " << playerAttack << endl;
    cout << "AI Attack roll is: " << AIAttack << endl;
    cout << "Player Def roll is: " << playerDefence << endl;
    cout << "AI Def roll is: " << AIDefence << endl;    
    cout << "testBattle2" << endl;
    if (AIAttack>playerAttack)
    {
        cout << "TestBattleAIWin" << endl;
        if (AIAttack>2*playerAttack)
        {
            cout << "AI wiped out your army!" << endl;
        }
        else
        {
            cout << "AI won the battle!" << endl;
            int threshold = static_cast<double>(AIAttack) - (static_cast<double>(AIAttack)*(static_cast<double>(AIDefence)/static_cast<double>(playerAttack)));
            cout << "Threshold : " << threshold << endl << flush;
            delTroops(threshold, map_ID, player_ID, "AI");
        }
    }
    else if (playerAttack>AIAttack)
    {
        cout << "TestBattlePlayerWin" << endl;
        if (playerAttack>2*AIAttack)
        {
            cout<< "You wiped out the AI army!" << endl;
            
        }
        else
        {
            cout << "You won the battle!" << endl;
            int threshold = static_cast<double>(playerAttack) - (static_cast<double>(playerAttack)*(static_cast<double>(playerDefence)/static_cast<double>(AIAttack)));
            cout << "Threshold : " << threshold << endl << flush;
            delTroops(threshold, map_ID, player_ID, "Player");
        }
    }
    else if (playerAttack==AIAttack)
    {
        cout << "Whatever" << endl;
    }
}

main()
{
    battle(4, 1, 6);
}
