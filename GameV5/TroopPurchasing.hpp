#ifndef TROOPPURCHASE_H
#define TROOPPURCHASE_H

#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;

class TroopPurchasing{

    public:
        int amountUnits();

        int mapArea();

        void purchaseUnitIterator(int player_ID, int troop_ID, int map_ID);

        int execute(int player_ID, int troop_ID);
};

#endif