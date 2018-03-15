#include <iostream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <unistd.h>
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
};