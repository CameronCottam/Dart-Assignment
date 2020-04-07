#pragma once
#include <iostream>
#include "Players.h"
using namespace std;

class Dart_Board
{
private:
	int Dartboard[2][20] = //This is are Dartboard variable array, which stores all the values on a dartbard
	{ {20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
	{18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
public:
	~Dart_Board(); // We call to a destructor to clean up and deallocate memory once the dartsboard class has been deleted
	int getDartboard(int Position1, int Position2); // This is a getter function, which we pass in position1(either 1 or 0) and position 2 which can range from 0 - 19(array positions)
	void Start_Off_Throw(Players &Player); //This is are StartOffThrow function, this decides who will throw first in a game
	void SingleShot(Players& Player, int Target); // This is the SingleShot function, and we pass in a player object and a target number
	void DoubleShot(Players& Player, int Target); // This is the DoubleShot function, and we pass in a player object and a target number
	void TrebleShot(Players& Player, int Target); // This is the TrebleShot function, and we pass in a player object and a target number
	void Bullseye(Players& Player); // This is the Bullseye function, and we pass in a player object
};

