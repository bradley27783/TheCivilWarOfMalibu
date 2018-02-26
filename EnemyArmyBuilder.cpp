#include <iostream>
#include <random> //using this to generate random number
#include <vector> //using vector because database is dynamic and do not know how many troop types in database; therefore, vector is easier because it does not require an upper limit to be defined

using namespace std;

struct SoldierInfo  //class for storing variables related to soldiers/troops
{
	vector<string> soldierNames = { "HoloSoldier", "HoloBike", "HoloTank", "HoloXcom" };
	vector<int> soldierAttackValues = { 10, 25, 60, 100 };

	vector<int> individualWeights; //vector to store weighted values, so weaker troops are chosen more often
	int totalWeights = 0; //stores maximum value for random integer, to store later
	double totalTroopAttack = 0; //stores attack value of all troops added together, to use for creating a weighted troop-picker
};

void enemyArmyBuild(int playerAttackVal)
{
	SoldierInfo currentInfo; //creates object from struct, to interact with

	for (int troopAttack : currentInfo.soldierAttackValues)
	{
		currentInfo.totalTroopAttack += troopAttack;
	}

	vector<string> enemyTroops; //stores troops in enemy army
	int enemyAttackVal = 0; //stores attack value of enemy army

							//below two integers are const because the value does not need to change
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

		//int randNum = rand() % currentInfo.totalWeights + 1; //generates random number between weighted values (1 and the total weight)

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

}
