#include "Dart_Board.h"
int Dart_Board::getDartboard(int Position1, int Position2)
{
	return Dartboard[Position1][Position2]; // This simply returns value found in the dartboard array
}
Dart_Board::~Dart_Board() // The destructor, to cleanup after the dartsboard has been deleted
{
	cout << "DartBoard destuctor called" << endl;
}
void Dart_Board::Start_Off_Throw(Players& Player) // This is are ThrowOff function, which sets the target for the Player, which will be used in a function in the Game.cpp file
{
	int random = rand() % 100 + 1; // Random Number generator
	if (random < (Player.getRate() - 15)) // if the random is less than the (plyers - 15), it will set the set the target to 50 
	{
		Player.setTarget(50);
	}
	else if (random < (Player.getRate() - 25))
	{
		Player.setTarget(25);
	}
	else if (random < Player.getRate())
	{
		Player.setTarget(1 + rand() % 20); //If this condition is triggered then the target will be a random number from 1 to 20
	}
	else
	{
		Player.setTarget(0);
	}
}
void Dart_Board::SingleShot(Players& Player, int Target) //SingleShot function, which we pass in the a player object and a target integer in the parameter
{
	int random = rand() % 100 + 1;
	if (random < (Player.getRate()))
	{
		//This is repeated throughout this function and the other shot type functions
		Player.setHits();  //This function simply adds a 1 to the Player's hit counter
		Player.setHitorMiss(true); // This function sets the Player's HitorMiss boolean to true
		Player.setScore(Target); //This will decrease the players score based on the target that was passed int
	}
	else if (random < (Player.getRate() - 10))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(Dartboard[0][Target]); //This will decrease the players score based on number from the Dartboard array with position 0 and the target number
	} 
	else if (random < (Player.getRate() - 15))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(Dartboard[1][Target]);  //This will decrease the players score based on number from the Dartboard array with position 1 and the target number
	}
	else
	{
		Player.setMisses(); //This adds a 1 to the Player's miss counter
		Player.setHitorMiss(false); // This sets the HitorMiss boolean to false
	}
}
void Dart_Board::DoubleShot(Players& Player, int Target)
{
	int random = rand() % 100 + 1;
	if (random < Player.getRate())
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(2 * Target); // This time the target will be times by two, to show the effect of the double shot
	}
	else if (random < (Player.getRate() - 10))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(2 * Dartboard[0][Target]); // This time the value from the dartboard array from position 0 and the target number will be times by two
	}
	else if (random < (Player.getRate() - 15))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(2 * Dartboard[1][Target]); // This time the value from the dartboard array from position 1 and the target number will be times by two
	}
	else if (random < (Player.getRate() - 20))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(Target); // This if the user is unable to get a double shot, there is a chance to hit a single shot
	}
	else
	{
		Player.setMisses();
		Player.setHitorMiss(false);
	}
}
void Dart_Board::TrebleShot(Players& Player, int Target)
{
	int random = rand() % 100 + 1;
	if (random < Player.getRate())
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(3 * Target); // The target will be times by 3 to shows the effect of a trebleshot
	}
	else if (random < (Player.getRate() - 10))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(3 * Dartboard[0][Target]); // This time the value from the dartboard array from position 0 and the target number will be times by three
	}
	else if (random < (Player.getRate() - 15))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(3 * Dartboard[1][Target]); // This time the value from the dartboard array from position 1 and the target number will be times by three
	}
	else if (random < (Player.getRate() - 20))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(Target); // If th player miss the chance to get a treble shot, there is a chance to a single shot
	}
	else
	{
		Player.setMisses();
		Player.setHitorMiss(false);
	}
}

void Dart_Board::Bullseye(Players& Player)
{
	int random = rand() % 100 + 1;
	if (random < Player.getRate())
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(50); // This will decrease the player's score by 50 to show that the user has hit a bullseye
	}
	else if (random < (Player.getRate() - 10))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(25); // This will decrease the player's score by 25 to show that the user has hit the outer ring
	}
	else if (random < (Player.getRate() - 15))
	{
		Player.setHits();
		Player.setHitorMiss(true);
		Player.setScore(1 + rand() % 20); // This will decrease the player's score by from a random number from 1 to 20
	}
	else
	{
		Player.setMisses();
		Player.setHitorMiss(false);
	}
}