#include <iostream>
#include <random> //using this to generate random number
#include <vector> //using vector because database is dynamic and do not know how many troop types in database; therefore, vector is easier because it does not require an upper limit to be defined

#include "libsqlite.hpp"

using namespace std;

struct SoldierInfo  //class for storing variables related to soldiers/troops
{
	vector<string> soldierNames;
	vector<int> soldierAttackValues;

	vector<int> individualWeights; //vector to store weighted values, so weaker troops are chosen more often
	int totalWeights = 0; //stores maximum value for random integer, to store later
	double totalTroopAttack = 0; //stores attack value of all troops added together, to use for creating a weighted troop-picker
};

void enemyArmyBuild(int playerAttackVal)
{
	
	SoldierInfo currentInfo; //creates object from struct, to interact with

	sqlite::sqlite db("civilwarofMalibu.db"); //connect to database
	auto cur = db.get_statement(); //set cursor
	
	cur->set_sql(
		"SELECT Name, Attack "
		"FROM military_Units;"); //get required troop data from relevant table in database (using multiple lines to make SQL code clearer)
	
	cur->prepare();
    
	while (cur->step()) //while loop to import all relevant data from database into struct
	{
		currentInfo.soldierNames.push_back(cur->get_text(0));
		currentInfo.soldierAttackValues.push_back(cur->get_int(1));
	}

	for (int troopAttack : currentInfo.soldierAttackValues)
	{
		currentInfo.totalTroopAttack += troopAttack;
	}

	vector<string> enemyTroops; //stores troops in enemy army
	int enemyAttackVal = 0; //stores attack value of enemy army

	//below two integers are const because the value does not need to change, 
	//and they are ints instead o floats/doubles because precision is not needed
	const int minPerc = 0.9 * playerAttackVal; //defines minimum attack value enemy army can have in relation to player's army
	const int maxPerc = 1.1 * playerAttackVal; //defines maximum attack value enemy army can have in relation to player's army

	for (double troopAttack : currentInfo.soldierAttackValues) //for loopcalculates weights to decide how often troops are chosen for the enemy army in here
	{
		int tempWeight = (1 - (troopAttack / currentInfo.totalTroopAttack)) * 100; //formula for calculating individual weight of one troop; weaker ones have higher numbers
		currentInfo.individualWeights.push_back(tempWeight);
		currentInfo.totalWeights += tempWeight;
	}


	while (minPerc >= enemyAttackVal) //loop means program keeps trying to build army until minimum is reached
	{
		//note: using random number generator from http://www.cplusplus.com/reference/random/mt19937/
		//because rand(), which is standard generator, always returned the same values, so there
		//was no variety for enemy armies. Also, rand() does not have a universal distribution,
		//so it does not work very well to generate more "random" numbers (all computers can only
		//generate pseudo-random numbers, but some are more random than others).
		
		random_device randGen; //random number generator
		mt19937 generator(randGen()); //mt19937 is an implementatino of a random number class
		uniform_int_distribution<int> distr(1, currentInfo.totalWeights); //defines range for random number
		int randNum = distr(generator);  //gets a number from the random number generator

		int counter = 0; // variable to track index
		int weightCheck = 0; //variable to keep track of weight (for checking which troop the current random number represents)

		for (int currentWeight : currentInfo.individualWeights)
		{
			weightCheck += currentWeight; //adds current weight to track
			if (randNum <= weightCheck) //checks if weighted number fits this value; if it doesn't, then next weight is tried
			{
				if (currentInfo.soldierAttackValues[counter] + enemyAttackVal <= maxPerc) //makes sure adding this troop doesn't make the enemy army too strong
				{
					enemyAttackVal += currentInfo.soldierAttackValues[counter];
					enemyTroops.push_back(currentInfo.soldierNames[counter]);	
					break; 
					//break this loop and generate another random number, 
					//because the appropriate number has been found for this random number
				}
			}
			else
			{
				counter++; //increments counter by one so next index is tried afterwards
			}
		}
	}

	//testing code below
	int soldier = 0;
	int bike = 0;
	int tank = 0;
	
	int xcom = 0;
	for (string troop : enemyTroops)
	{
		if (troop == "HoloSoldier")
		{
			soldier += 1;
		}
		else if (troop == "HoloBike")
		{
			bike += 1;
		}
		else if (troop == "HoloTank")
		{
			tank += 1;
		}
		else if (troop == "HoloXcom")
		{
			xcom += 1;
		}
	}
	
	cout << "Holosoldiers: " << soldier << endl;
	cout << "HoloBikes: " << bike << endl;
	cout << "HoloTanks: " << tank << endl;
	cout << "HoloXcoms: " << xcom << endl;
	cout << "Total attack value: " << enemyAttackVal << endl;
	
	/*
    for (string name : currentInfo.soldierNames)
    {
        cout << "Name: " << name << endl;
    }
    for (int atkval : currentInfo.soldierAttackValues)
    {
        cout << "Attack value: " << atkval << endl;
    }
    for (int test : currentInfo.individualWeights)
    {
        cout << test << endl;
    }
    cout << currentInfo.totalWeights << endl;*/
}
