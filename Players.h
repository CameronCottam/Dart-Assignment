#pragma once
#include <iostream>
#include <conio.h>
using namespace std;
class Players
{
private:
	int rate; // Player's success rate
	int score; // Player's Score
	int target; // Player's Target
	int legs; // Player's leg wins
	int darts; // Player's dart counter
	double MatchWinFrequncy; // Average leg wins
	double DartFrequncy[9]; // Frequncy table
	int Sets; // The sets counter
	bool HitorMiss; // Checks if the user hit or missed the board
	int hit; // Hit counter
	int miss; // Miss counter
	string name; // Player's name
	int ScoreHold; // This will hold the player's previous score before, they every three shots. This is used incase the player goes past 0 or is equivalent to 1
	
public:
	//Constructors & Destructors
	Players(string PlayerName, int PlayerRate);
	~Players();
	// Get Functions
	string getName();
	int getRate();
	int getScore();
	int getTarget();
	int getLegs();
	int getDarts();
	double getMatchWinFrequncy();
	double getDartFrequncy(int position);
	int getSets();
	bool getHitOrMiss();
	int getHits();
	int getMisses();
	//Set Functions
	void setName();
	void setRate();
	void setScore(int Point);
	void setTarget(int NewTarget);
	void setLegs();
	void setDarts();
	void setMatchWinFrequncy(int GameCounter);
	void setDartFrequncy(int counter);
	void setSets();
	void setHitorMiss(bool Checker);
	void setHits();
	void setMisses();

	//Functions used to reset stats/alter/check  the stats of the player
	void ResetAllStats(); // This will reset the following stats to zero after a player has won a set. (legs, darts, hits, miss)
	void ScoreCheck(); // This will check the score and will replace the score, if it meets certain conditions
	void setStats(); //This will reset the player's score back to 501 and the following variables: darts, hits, niss to zero
	void ResetLegs(); // This will reset the leg counter, once it's reached 5
};

