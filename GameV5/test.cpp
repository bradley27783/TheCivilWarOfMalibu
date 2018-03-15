#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include "playerInfo.hpp"

using namespace std;

#include "libsqlite.hpp"

int main(){
    
    int player_ID = 1;
    PlayerInfo pinfo;
    pinfo.get_playerIncome(player_ID);
}