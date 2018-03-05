#include <iostream>
#include <sstream>
using namespace std;

/* Declarations */
void checker();
void toServer();
void fromServer();
void help();
void showScreen();
void breakScreen();
int main();

/*Variables */
char knownWords [5][10] = {"look","inspect","use","break","help"};/*Words the user can use to interact*/
char knownObjects [1][10] = {"screen"};

void checker(string input)
{
	

	string inputArr[4];
	int i =0;

	/* Splits the input into array */
	stringstream ssin(input);
	while(ssin.good() && i < 4)
	{
		ssin >> inputArr[i];
		++i;
	}
	for(int j=0;j<sizeof(inputArr);j++)
	{
		for(int i=0;i<sizeof(knownWords);i++)
		{
			if(inputArr[j] == knownWords[i])
			{
				cout << "showing4 ";
				cout << inputArr[j+1] << endl;
				/*Look & inspect*/
				if((i==0 || i==1) && (inputArr[j+1] == knownObjects[0]))
				{
					cout << "showing5 ";
					showScreen();
				}
				/*use*/
				else if(i==2 && inputArr[j+1] == knownObjects[0])
				{
					showScreen();
				}
				/*break*/
				else if(i==3 && inputArr[j+1] == knownObjects[0])
				{
					breakScreen();
				}
				/*help*/
				else if(i==4)
				{
					help();
				}
			}
		}
	}
	cout << "You can't do that!" << endl;
	main();
}

void help()
{
	cout << "------HELP------" << endl;
	cout << "All objects are in CAPS" << endl;
	cout << "----------------" << endl;
	cout << "Use of keywords:" << endl;
	cout << "'keyword' + 'object'" << endl;
	cout << "----------------" << endl;
	cout << "Keywords are as follow: " << endl;
	cout << "Look & Inspect: Used to show a description or trigger an event" << endl;
	cout << "Use: Used to use an object or trigger an event." << endl;
	cout << "Help: You know this one!" << endl;
	main();
	
}

void showScreen()
{
	cout << "Interface id: 7743" << endl;
	cout << "Start (1), Load(2), Help(3)" << endl;

	while(true)
	{
		string input;
		cout << "ENTER_> ";
		cin >> input;

		if(input == "1")
		{
			/*Intergration here*/
		}

		else if(input == "2")
		{
			/*Server intergration here*/
		}

		else if(input == "3")
		{
			help();
		}
		else
		{
			cout << "You can't do that" << endl;
		}
	}
	main();
}

int main()
{
		cout << "'Welcome to the Civil War of Malibu, Commander', a voice reported," << endl;
		cout << "Have you signed into the local interface?" << endl;
		cout << "In front of you is a SCREEN." << endl;
		cout << "... -- type 'Help' for help." << endl;

		while(true)
		{
			string input;
			cout << "ENTER_> ";
			cin >> input;

			/*tolower(input);*/

			checker(input);
		}

}

void breakScreen()
{
	cout << "Why? That is my question for you." << endl;
	cout << "Was it desperate need to ruin what little" << endl;
	cout << "I had? Or was it to find a secret hidden?" << endl;
	cout << "Well, here it is." << endl;
	cout << "..." << endl;
	cout << "Happy?" << endl;
	cout << "Good." << endl;
	main();
}
