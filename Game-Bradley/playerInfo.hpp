#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <iostream>
#include <string>
using namespace std;
#include "libsqlite.hpp"


class PlayerInfo{
    public:
        int get_playerID();
        int playerCreation(string user_Input);
        int get_playerTurns(int player_ID);
        int checkPlayer();
        string create_playerID();
        int get_playerMoney(int player_ID);
        int get_playerIncome(int player_ID);
};

#endif