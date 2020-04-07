#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <math.h>
#include "Players.h"
#include "Dart_Board.h"
#include "Graphics.h"

using namespace std;
class Game
{
private:
	//Varaiables
	int Decision; // Used in the intial setup stage
	int GameMode; // Used to select which gamemodes
	double Sets; // How many sets, the user would like to play 
	char ShotType; // The type of shot the user would like to throw
	int SimSets; // Used as a counter to indicate how many sets of games have been played
	int Target; // The users target on the darboard
	int Average_Counter; // The average counter used for the Win Frequncy 
	double Average_Counter2; // The average counter used for the Win Frequncy 
	bool Turn; // The boolean Turn is used to decided who goes in first throwing
	bool EndingShot; // Boolean is used to indicate if the user's throw was a single
	int frequncy; // The fequncy
public:
	Game(); //Constructor
	~Game(); //Destructor
	int Play(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard); // This is the main Game function, which calls to other functions.
	void GameSettings(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard); // THe user inputs the details for what kind of game, they would like to play
	void ThrowOff(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard); // This throwOff function, decides which player throws first
	void Player_Targeting(Graphics& GraphicFront, Players& Player, Dart_Board& Dartboard); //This is the players Input for the targeting system
	void WinCheck(Players& Player1, Players& Player2); // The win check function to see if the player has won the game/set
	void SuggestTarget(Graphics& GraphicFront, Players& Player, Dart_Board& Dartboard); // This function is used in PlayervPlayer & PlayervAI modes. It displays the best target to aim for.
	int AI_Targeting(Players& Player, Dart_Board& Dartboard); // This is the AI Targeting Function
	//GameModes
	void GameTypes(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard); // This includes the AIvAI, PlayervAI, and, PlayervPlayer Gamemodes. Which are selected in GameSettings
	void SinglePlayer(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard); // The SinglePlayer Mode
};