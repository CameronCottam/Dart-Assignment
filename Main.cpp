#include <iostream>
using namespace std;
#include "Game.h" //We only include the Game header as that contains the rest of the classes in the Games includes
int main()
{
	srand((unsigned)time(NULL));
	Players Player1("Joe", 71); //We declare the first object called Player One and use a constructor to pre-define the players details and we pass in the default name and rate for Joe
	Players Player2("Sid", 73); //We declare the first object called Player Two and use a constructor to pre-define the players details and we pass in the default name and rate for Sid
	Graphics GraphicFront; //This creates the an object to the Graphics Class and we call it GraphicFront
	Dart_Board Dartboard; //This creates an object to the Dartboard class
	Game Game; // This creates an object to the Game Class
	Game.Play(GraphicFront, Player1, Player2, Dartboard); // We then execute the Game.play function, which starts the whole game.
}