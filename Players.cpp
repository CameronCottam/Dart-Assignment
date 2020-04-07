#include "Players.h"
Players::Players(string PlayerName, int PlayerRate) // The player constructor
{
	rate = PlayerRate;
	score = 501;
	target = 0;
	legs = 0;
	darts = 0;
	MatchWinFrequncy = 0.00;
	for (int i = 0; i < 9; i++)
	{
		DartFrequncy[i] = { 0 };
	}
	Sets = 0;
	HitorMiss = false; 
	hit = 0;
	miss = 0;
	ScoreHold = 0;
	name = PlayerName;
}

Players::~Players() // The Player destructor, to cleanup after the player objects have been deleted
{
	cout << "Player Destructor has been called" << endl;
}

//These are get functions that will return values of the player
string Players::getName()
{
	return name;
}
int Players::getRate()
{
	return rate;
}
int Players::getScore()
{
	return score;
}
int Players::getTarget()
{
	return target;
}
int Players::getLegs()
{
	return legs;
}
int Players::getDarts()
{
	return darts;
}
double Players::getMatchWinFrequncy()
{
	return MatchWinFrequncy;
}
double Players::getDartFrequncy(int position)
{
	return DartFrequncy[position];
}
int Players::getSets()
{
	return Sets;
}
bool Players::getHitOrMiss()
{
	return HitorMiss;
}
int Players::getHits()
{
	return hit;
}
int Players::getMisses()
{
	return miss;
}

//		Set Functions, Assigns new values to the variables
void Players::setName() //Changes the player's name
{
	cout << "Enter you're name" << endl; 	
	cin >> name;
}
void Players::setRate() //This will change the player's rate to a random number
{
	bool loop = false;
	while (loop != true) //We use a while loop to constantly overprint a new random number
	{
		system("cls");
		int random = rand() % 100 + 1;
		cout << "\t\t\t\t\t\t\t\t\t" << random << endl;
		cout << "\t\t\t\t\t\t\t\t\t" << "Press space to stop"<< endl;
		cout << "\t\t\t\t\t\t\t\t\t" << "Player:" <<  name << endl;


		if (_kbhit())
		{
			char key = toupper(_getch()); // To end the loop, the user must press the space par, once that has been executed, it will then end the loop and assign the random number to the rate
			if (key == ' ')
			{
				loop = true;
				rate = random;
			}
		}
	}
	system("cls");
	cout << "\t\t\t\t\t\t\t\t\t" << "This is player "<< name << "'s new rate:" << rate << endl;

}
void Players::setTarget(int NewTarget) //We pass in a NewTarget in the parameter, which is then assigned to the target variable
{
	target = NewTarget;
}
void Players::setLegs() //This will add a one to the legs counter
{
	legs += 1;
}
void Players::setDarts() //This will add a one to the darts counter
{
	darts += 1;
}
void Players::setMatchWinFrequncy(int GameCounter) //This will set the Players win frequncy. For example, if each player wins one set out of 3, the frequncy would be 50%
{
	MatchWinFrequncy = ((double)Sets) / GameCounter; //We pass in a game counter variable to which then divides the sets by the game counter.
	MatchWinFrequncy = MatchWinFrequncy * 100;
}
void Players::setDartFrequncy(int counter)
{
	DartFrequncy[darts - 8] = ((double)counter) / legs * 100;
	for (int i = 0; i < darts; i++)
	{
		if (DartFrequncy[i] > 0)
		{
			DartFrequncy[i] = { ((double)counter) / hit * 100 };
		}
	}
}
void Players::setSets() //This will add a one to the Sets counter
{
	Sets += 1;
}
void Players::setHitorMiss(bool Checker) //We pass in a boolean checker, that will assign the condition(true or false) from the Checker to the HitorMiss
{
	HitorMiss = Checker;
}
void Players::setHits() //This will add a one to the hits counter
{
	hit += 1;
}
void Players::setMisses() //This will add a one to the miss counter
{
	miss += 1;
}

void Players::ResetAllStats() //This will reset the stats, if the user wants to setup another Game.
{
	score = 501;
	Sets = 0;
	legs = 0;
	darts = 0;
	hit = 0;
	miss = 0;
	for (int i = 0; i < 9; i++)
	{
		DartFrequncy[i] = { 0 };
	}
	MatchWinFrequncy = 0.00;
}
void Players::setStats() // This will reset the stats after a leg has been achieved
{
	score = 501;
	darts = 0;
	hit = 0;
	miss = 0;
}
void Players::setScore(int Point) //This will decrease the players score based on the target number in the Dartboard class
{
	score = score - Point;
}
void Players::ScoreCheck()
{
	if (score >= 2) //If the score is greater than or equal to 2, then it will asign the value from the player's score to the variable called ScoreHold
	{
		ScoreHold = score;
	}
	else if (score < 0 || score == 1) //Else if the score is less than zero OR the score is equivant to 1. Then it will assign the value from ScoreHold to the variable called score 
	{
		score = ScoreHold;
	}
}
void Players::ResetLegs() // This will reset the leg counter to zero
{
	legs = 0;
}