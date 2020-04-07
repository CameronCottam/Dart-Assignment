#include "Game.h"
Game::Game() // Constructor is used to define the variables
{
	Decision = 0;
	GameMode = 0;
	Sets = 0;
	ShotType = ' ';
	SimSets = 0;
	Target = 0;
	Average_Counter = 0;
	Average_Counter2 = 0;
	Turn = false;
	EndingShot = false;
	frequncy = 0;
}
Game::~Game()
{
	cout << "The Game destructor is called" << endl;
}
int Game::Play(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard)
{
	GraphicFront.initiate_Graphics(); // This will initiate the graphics
	srand((unsigned)time(NULL)); 
	GameSettings(GraphicFront, Player1, Player2, Dartboard); //This is the game  settings, which acts as the base for setting up matches and game modes
	system("cls");
	while (Player1.getSets() != Sets|| Player2.getSets() != Sets) // While the Player 1 or Player 2 sets do not equal half of the sets (See Game Settings for how this was done), It will exeuctes this loop
	{
		switch (GameMode) // We use a Swtich statement to better access the GameModes
		{
		case 1: //If the user enter one, it will execute the Game Types function
			GameTypes(GraphicFront, Player1, Player2, Dartboard); 
			break;
		case 2: //If the user enter two, it will executre the Single Player function
			SinglePlayer(GraphicFront, Player1, Player2, Dartboard);
			break;
		default: //If the user entered a wrong number at the beginning stages, this default statement will allow them to fix their mistake
			GameSettings(GraphicFront, Player1, Player2, Dartboard);
			break;
		}
		if (Player1.getSets() == Sets || Player2.getSets() == Sets) // If Player one or Player two's sets are equivalent to the Sets. It will display the winner and ask the user if they want to setup another game
		{
			system("cls");
			GraphicFront.GameDisplay(Player1, Player2);
			GraphicFront.DrawString(61, 31, "Would you like to play again or try a different mode[Y/N]?");
			if (Player1.getSets() > Player2.getSets()) // IF statement is used to which player has won
			{
				GraphicFront.DrawString(61, 30, "Player: "); cout << Player1.getName() << " wins the game!"<< endl; 
			}
			else
			{
				GraphicFront.DrawString(61, 30, "Player: "); cout << Player2.getName() << " wins the game!" << endl;
			}
			cin >> ShotType; // Asks the user if they would like to setup another game
			if (ShotType == 'Y' || ShotType == 'y')
			{
				Player1.ResetAllStats(); //Resets the player's stats to the beginning
				Player2.ResetAllStats();
				Average_Counter = 0;
				frequncy = 0;
				GameSettings(GraphicFront, Player1, Player2, Dartboard); //Executes the Game Settings function
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

void Game::SinglePlayer(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard) // The single player mode
{
	for (int i = 0; i < 3; i++) //To simulate three throws
	{
		GraphicFront.GameDisplay(Player1, Player2);
		GraphicFront.DrawString(30, 0, "Maximum Sets:"); cout << SimSets << endl; // This will display the max sets that the user entered at the beginning
		GraphicFront.DrawString(30, 1, "Number of sets to win:"); cout << Sets << endl; // This will display the number of sets the player's need to win the game
		GraphicFront.DartboardStatus(Player1);
		GraphicFront.DrawString(70, 0, "Current Turn: "); //Displays who's turn
		cout << Player1.getName() << endl;
		Player_Targeting(GraphicFront, Player1, Dartboard); // Calls to the PlayerTargeting function and pass in the GraphicFront, Player1, and, dartboard
		if (Player1.getScore() == 0 && EndingShot == true) //This statement executes if the player has reached zero either from the first and second series of darts thrown
		{
			WinCheck(Player1, Player2);
			i = 3;
		}
	}
	Player1.ScoreCheck();
	WinCheck(Player1, Player2);
}

void Game::GameTypes(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard) // The Game Types function contains the three other modes. Which are the following: PlayervPlayer, PlayervAI, and, AIvAI
{ //The Game Types function was slighty adapted from the single player function to better suit the game modes
	
	if (Turn == true) // If the turn is equivalent to true, then the first throw will be player one
	{
		for (int i = 0; i < 3; i++)
		{
			GraphicFront.GameDisplay(Player1, Player2);
			GraphicFront.DartboardStatus(Player1);
			GraphicFront.DrawString(70, 0, "Current Turn: ");
			//cout << Player1.getName() << endl;

			if (Decision == 1 || Decision == 2) //If the Decision variable is equivalent to one or two then the Player is throwing first
			{
				Player_Targeting(GraphicFront, Player1, Dartboard);
			}
			else if (Decision == 3) //If the Player selected AIvAI then AI targeting verison of player one will throw first
			{
				AI_Targeting(Player1, Dartboard);
			}

			if (Player1.getScore() == 0 && EndingShot == true)
			{
				WinCheck(Player1, Player2);
				i = 3;
			}
			system("cls");
		}
		Player1.ScoreCheck();
		WinCheck(Player1, Player2);
	}
	else // if Turn is not equivalent to true then Player two will throw first
	{
		for (int i = 0; i < 3; i++)
		{
			GraphicFront.GameDisplay(Player1, Player2);
			GraphicFront.DartboardStatus(Player2);
			GraphicFront.DrawString(70, 0, "Current Turn: ");
			cout << Player2.getName() << endl;
			if (Decision == 1) //If Decision is equivalent to 1 (PlayervPlayer) then Player2 will throw first
			{
				Player_Targeting(GraphicFront, Player2, Dartboard);
			}
			else if (Decision > 1) //If the Decision is greater than 1 then the AI verison of Player2 will throw first 
			{
				AI_Targeting(Player2, Dartboard);
			}
			if (Player2.getScore() == 0 && EndingShot == true)
			{
				WinCheck(Player1, Player2);
				i = 3;
			}
			system("cls");
		}
		Player2.ScoreCheck();
		WinCheck(Player1, Player2);
	}
	GraphicFront.GameDisplay(Player1, Player2);
	if (Turn == true) // If Turn is equivalent to true then Player Two will throw after player one's turn is over
	{
		for (int i = 0; i < 3; i++)
		{
			GraphicFront.GameDisplay(Player1, Player2);
			GraphicFront.DartboardStatus(Player2);
			GraphicFront.DrawString(70, 0, "Current Turn: ");
			cout << Player2.getName() << endl;

			if (Decision == 1)  //If Decision is equivalent to 1 (PlayervPlayer) then Player2 will throw after player one's turn is over
			{
				Player_Targeting(GraphicFront, Player2, Dartboard);
			}
			else if (Decision > 1) //If Decision is greater than 1 then  the AI verison of Player2 will throw after player one's turn is over
			{
				AI_Targeting(Player2, Dartboard);
			}
			if (Player2.getScore() == 0 && EndingShot == true)
			{
				WinCheck(Player1, Player2);
				i = 3;
			}
			system("cls");
		}
		Player2.ScoreCheck();
		WinCheck(Player1, Player2);
	}
	else // If turn is not equivalent to true then Player one will throw after player one's turn is over
	{
		for (int i = 0; i < 3; i++)
		{
			GraphicFront.GameDisplay(Player1, Player2);
			GraphicFront.DartboardStatus(Player1);
			GraphicFront.DrawString(70, 0, "Current Turn: "); cout << Player1.getName() << endl;
			if (Decision == 1 || Decision == 2) //If Decision is equivalent to 1 or 2 then Player1 will throw after player Two's turn is over
			{
				Player_Targeting(GraphicFront, Player1, Dartboard);
			}
			else if (Decision == 3) //If Decision is equivalent to 3 then the AI verison of Player1 will throw after player Two's turn is over
			{
				AI_Targeting(Player1, Dartboard);
			}
			if (Player1.getScore() == 0 && EndingShot == true)
			{
				WinCheck(Player1, Player2);
				i = 3;
			}
			system("cls");
		}
		Player1.ScoreCheck();
		WinCheck(Player1, Player2);
	}
}

void Game::GameSettings(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard) // This function is used to setup settings for the game,
{
	//These drawStrings are used to display the text for setting up a game
	GraphicFront.DrawString(75, 0, "Select which Gamemode?");
	GraphicFront.DrawString(75, 1, "1 = (AI or Player) vs (AI or Player)");
	GraphicFront.DrawString(75, 2, "2 = SinglePlayer");
	GraphicFront.DrawString(75, 3, "Choose:"); 
	cin >> GameMode; //This will ask the user pick which GameMode
	GraphicFront.DrawString(75, 5, "Would you like to change you're details of you're player(name/rate)[Y/N]: ");
	cin >> ShotType; //This will ask if th user wants to change any details about the player. i.e. Name and/or rate
	if (ShotType == 'y' || ShotType == 'Y')
	{
		GraphicFront.ClearScreen();
		GraphicFront.DrawString(75, 7, "Which player?");
		GraphicFront.DrawString(75, 8, "1 = Player One");
		GraphicFront.DrawString(75, 9, "2 = Player Two");
		GraphicFront.DrawString(75, 10, "3 = Both Players");
		GraphicFront.DrawString(75, 11, "Choose:");
		if (GameMode == 2) // if the GameMode was only 2 (single player) it will automatically assign one to the decision variable
		{
			Decision = 1;
		}
		else
		{
			cin >> Decision; // Asks the user to pick which player, they want to alter details off. There is an option for both
		}
		if (Decision == 1) // This is for alternating Player One's details
		{
			system("cls");
			GraphicFront.DrawString(75, 13, "Would you like to change to you're (1)name or (2)rate or (3)both");
			GraphicFront.DrawString(75, 14, "Choose:");
			cin >> Decision; // This will ask the user to choose, if they would like to change their name or rate or both
			if (Decision == 1) //The IF statements will execute functions, in the player class
			{
				Player1.setName();
			}
			else if (Decision == 2)
			{
				Player1.setRate();
			}
			else
			{
				Player1.setName();
				Player1.setRate();
			}
		}
		else if (Decision == 2) // This is for alternating Player Two's details
		{
			Player2.setRate();
			GraphicFront.DrawString(75, 13, "Would you like to change to you're name or rate or both");
			GraphicFront.DrawString(75, 14, "Choose:");
			cin >> Decision;
			if (Decision == 1)
			{
				Player2.setName();
			}
			else if (Decision == 2)
			{
				Player2.setRate();
			}
			else
			{
				Player2.setName();
				Player2.setRate();
			}
		}
		else // This is for alternating both player's stats details
		{
			GraphicFront.DrawString(75, 13, "Would you like to change to you're name or rate or both");
			GraphicFront.DrawString(75, 14, "Choose:");
			cin >> Decision;
			if (Decision == 1)
			{
				Player1.setName();
				Player2.setName();
			}
			else if (Decision == 2)
			{
				Player1.setRate();
				Player2.setRate();
			}
			else
			{
				Player1.setName();
				Player1.setRate();
			}
			
		}
	}

	if (GameMode == 1) // If the GameMode is equivalent to 1 then it will execute the ThrowOff function and ask the user to select what type of Game Mode 
	{
		ThrowOff(GraphicFront, Player1, Player2, Dartboard);
		GraphicFront.DrawString(75, 13, "Select the following?");
		GraphicFront.DrawString(75, 14, "1 = PlayervPlayer)");
		GraphicFront.DrawString(75, 15, "2 = PlayervAI");
		GraphicFront.DrawString(75, 16, "3 = AIvAI");
		GraphicFront.DrawString(75, 17, "Choose:"); cin >> Decision;
	}

	GraphicFront.ClearScreen();
	GraphicFront.DrawString(75, 19, "How many sets would you like to play?");
	GraphicFront.DrawString(75, 20, "");  
	cin >> SimSets; // Asks the user to input a value, which is then assigned to the variable called SimSets
	
	if (SimSets % 2 == 0) //Checks if Simsets is even
	{
		Sets = SimSets; //Assigns the value from SimSets to the variable called Sets
		Sets = Sets / 2 + 1; //Divides Sets by 2 then add one to it.
	}
	else
	{
		Sets = SimSets;
		Sets = round(Sets / 2); //if SimSets is an odd number then Sets is divided by 2 then rounded up. The value from the rounding is then assigned to the variable called Sets
	}

}

void Game::ThrowOff(Graphics& GraphicFront, Players& Player1, Players& Player2, Dart_Board& Dartboard) // This function decides which player will throw first
{
	Decision = 0;
	while (Decision == 0) // The reason for the loop is to prevent the case of both players having the same target number
	{
		Dartboard.Start_Off_Throw(Player1); // Executes the Start Off Throw function in the Dartboard class
		Dartboard.Start_Off_Throw(Player2);
		if (Player1.getTarget() > Player2.getTarget()) // If Player one's target is greater than Player 2 then Player one will throw first
		{
			Decision = 1;
			Turn = true;
			GraphicFront.DrawString(75, 6, "Player One will throw first");
		}
		else // else then Player two will throw first
		{
			Decision = 1;
			Turn = false;
			GraphicFront.DrawString(75, 6, "Player Two will throw first");
		}
	}
}

void Game::Player_Targeting(Graphics& GraphicFront, Players& Player, Dart_Board& Dartboard) // This is the Player Targeting function, which the user input for PlayerVs modes
{
	Player.setDarts(); // Adds a one to the Darts counter
	EndingShot = false; // The EndingShot boolean is to show if the player's final shot is a double or bullseye
	SuggestTarget(GraphicFront, Player, Dartboard); // This calls to the SuggestTarget function, which displays the best target for the player to aim for.
	//The DrawString functions display the type of shots the user should take
	GraphicFront.DrawString(61, 19, "ShotTypes:");
	GraphicFront.DrawString(61, 20, " __________________");
	GraphicFront.DrawString(61, 21, "| S - Single       |");
	GraphicFront.DrawString(61, 22, "| D - Double       |");
	GraphicFront.DrawString(61, 23, "| T - Treble       |");
	GraphicFront.DrawString(61, 24, "| B - Bullseye     |");
	GraphicFront.DrawString(61, 25, "|__________________|");
	GraphicFront.DrawString(61, 27, "Choose the type of shot to throw:");
	cin >> ShotType;
	if (ShotType == 'b' || ShotType == 'B') //If the ShotType is b then it will execute bullseye function in the Dartboard class
	{
		EndingShot = true; // Since it's a bullseye shot then EndingShot is now true
		Dartboard.Bullseye(Player); // This will trigger the Bullseye function and will skip the prompt that would ask the user to select a target
	}
	else
	{
		//If the user does not select the bullseye shot then it will ask the user to enter their target
		GraphicFront.DrawString(61, 28, "Target");
		cin >> Target;
		while (Target > 20) // If the user enters a number greater than 20, it will prompt the user to re-enter a valid number
		{
			GraphicFront.DrawString(61, 28, "Please enter a score within 1 - 20");
			cin >> Target;
		}
	}
	if (ShotType == 's' || ShotType == 'S')
	{
		Dartboard.SingleShot(Player, Target); // If the user enter an S for single shot then it will execute the SingleShot function in the Dartsboard class
	}
	else if (ShotType == 'd' || ShotType == 'D')
	{
		EndingShot = true; // Since this is a double shot then EndingShot equals true
		Dartboard.DoubleShot(Player, Target); // If the user enter a  D for doule shot then it will execute the DoubleShot function in the Dartsboard class
	}
	else if (ShotType == 't' || ShotType == 'T')
	{
		Dartboard.TrebleShot(Player, Target); // If the user enter a T for treble shot then it will execute the TrebleShot function in the Dartsboard class
	}
	system("cls");
}

int Game::AI_Targeting(Players& Player, Dart_Board& Dartboard) // This is the AI targeting function. This function is used for the AI to pick the most optimal target based on their score
{
	EndingShot = false;
	Player.setDarts(); // Adds a one to the Darts counter for the player
	if ((Player.getScore() - 50) == 0) // If the Player's score minus 50 is equivalent to 0, then it will execute the Bullseye function
	{
		Dartboard.Bullseye(Player);
		EndingShot = true;
		return 0;
	}
	else
	{
		for (int i = 1; i >= 0; i--) //This for loop is used for the left and right side on the dartboard
		{
			for (int j = 20; j >= 0; j--) //The for loop will count down from 20 to 0. 20 is the most optimal target in treble shots
			{
				if ((Player.getScore() - (j * 3)) >= 60) //If the player's score minus the variable J(which is multiplied by 3) is greater than or equal to 2. Then it execute the TrebleShot
				{
					Dartboard.TrebleShot(Player, j); //This calls to the TrebleShot Function, which we pass in the value J
					return 0;
				}
				else if ((Player.getScore() - (Dartboard.getDartboard(i, j) * 3)) >= 60) //If the player's score minus the variable J(which is multiplied by 3) is greater than or equal to 2. Then it execute the TrebleShot
				{
					Dartboard.TrebleShot(Player, (Dartboard.getDartboard(i, j) * 3)); //This calls to the TrebleShot Function, which we pass in the value J
					return 0;
				}
				else if ((Player.getScore() - (j * 2)) == 0) //If the Player's score minus the variable j(which is multiplied by 2) is equivalant to 0 then Double Shot is executed and we pass in the value in J 
				{
					Dartboard.DoubleShot(Player, j);  // This will execute, if the player's score will go to zero by a double shot
					EndingShot = true;
					return 0;
				}
				else if ((Player.getScore() - (Dartboard.getDartboard(i, j) * 2)) == 0) // If the Player's score minus the value from the Dartboard that is times by 2 is equivalent to 0. Then Double Shot is executed
				{
					
					Dartboard.DoubleShot(Player, Dartboard.getDartboard(i, j));
					return 0;
				}
				else if ((Player.getScore() - (j * 2)) >= 2) //If the player's score minus the variable J(which is multiplied by 2) is greater than or equal to 2. Then it execute the DoubleShot
				{
					Dartboard.DoubleShot(Player, j); 
					EndingShot = true;
					return 0;
				}
				else if ((Player.getScore() - j) >= 2)  //If the player's score minus the variable J is greater than or equal to 2. Then it execute the SingleShot
				{
					Dartboard.SingleShot(Player, j);
					return 0;
				}
			}
		}
	}
	return 0;
}

void Game::WinCheck(Players& Player1, Players& Player2) // This is the wincheck function, which checks if the player has won a leg or set
{
	
	if (Player1.getScore() == 0 && EndingShot == true) // If the Players score is equivalent to zero and EndingShot is equivalent to true then the player has won a leg
	{
		Average_Counter++; //Adds a 1 to the Average_Counter variable
		Player1.setLegs(); //Calls to the setLegs function
		Player1.setDartFrequncy(Average_Counter); //Calls to the setDartFrequncy in the Players class and I pass in the Average_Counter
		Player1.setStats(); //Calls to the setStats function
		Player2.setStats();
	}
	else if (Player2.getScore() == 0 && EndingShot == true)
	{
		Average_Counter++; //Adds a 1 to the Average_Counter variable
		Player2.setLegs();
		Player2.setDartFrequncy(Average_Counter); 
		Player1.setStats();
		Player2.setStats();
	}

	if (Player1.getLegs() == 5 || Player2.getLegs() == 5) //The first player to have 5 legs will win a set
	{
		frequncy++;
		if (Player1.getLegs() == 5) // If Player one has 5 legs then it will call to the setSets function in the player's class
		{
			Player1.setSets();
		}
		else
		{
			Player2.setSets();
		}
		//These are used to set the Win Frequncy and Resetting the legs
		Player1.ResetLegs();
		Player2.ResetLegs();
		Player1.setMatchWinFrequncy(frequncy);
		Player2.setMatchWinFrequncy(frequncy);
	}
}

void Game::SuggestTarget(Graphics& GraphicFront, Players& Player, Dart_Board& Dartboard) // The suggest target function, uses the  same algorithm as the AI Targeting. But is slighty adapted to be used for a player
{
	int State = 0; // The state variable is used to display the message 
	if ((Player.getScore() - 50) == 0) // The algorithm is used to assign a value to the player's target variable. Once that happens it will instanttly end the loop and assign a value from 1 - 4 to the variable called State
	{
		State = 0;
	}
	else
	{
		for (int i = 1; i >= 0; i--)
		{
			for (int j = 20; j >= 0; j--)
			{
				if ((Player.getScore() - (Dartboard.getDartboard(i, j) * 2)) == 0)
				{
					State = 2;
					Player.setTarget(Dartboard.getDartboard(i, j));
					i = 0;
					j = 0;
				}
				else if ((Player.getScore() - (j * 2)) == 0)
				{
					State = 2;
					Player.setTarget(j);
					i = 0;
					j = 0;
				}
				else if ((Player.getScore() - (j * 3)) >= 2)
				{
					State = 3;
					Player.setTarget(j);
					i = 0;
					j = 0;
				}
				else if ((Player.getScore() - (j * 2)) >= 2)
				{
					State = 2;
					Player.setTarget(j);
					i = 0;
					j = 0;
				}
				else if ((Player.getScore() - j) >= 2)
				{
					State = 1;
					Player.setTarget(j);
					i = 0;
					j = 0;
				}
			}
		}
	}
	switch (State) //This switch case statement will display the apporatie message based on what value was assigned to the variable called State from the aiming algorithm  
	{
	case 0:
		GraphicFront.DrawString(96, 20, "Suggested Target Bullseye");
		break;
	case 1:
		GraphicFront.DrawString(96, 20, "Suggested Target Single:"); cout << Player.getTarget() << endl;
		break;
	case 2:
		GraphicFront.DrawString(96, 20, "Suggested Target Double:"); cout << Player.getTarget() << endl;
		break;
	case 3:
		GraphicFront.DrawString(96, 20, "Suggested Target Treble: "); cout << Player.getTarget() << endl;
		break;
	}
}

