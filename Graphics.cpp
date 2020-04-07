#include "Graphics.h"
Graphics::~Graphics() 
{
	cout << "Graphics's destructor called" << endl;
}
void Graphics::initiate_Graphics()
{
	//This function will handle the information to the console to allow the graphics to work.
	COORD console_size = { 200, 200 }; // The size of the console 
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);
	SetConsoleScreenBufferSize(hconsole, console_size); 
	GetConsoleScreenBufferInfo(hconsole, &con_info);
}
void Graphics::DrawString(int x_axis, int y_axis, string text)
{
	//This function will display text based on what the x and y coordinates that were defined
	COORD cursor_pos; // used to pass coords 
	cursor_pos.X = x_axis; // X coordinates
	cursor_pos.Y = y_axis;// Y coordinates
	SetConsoleCursorPosition(hconsole, cursor_pos);
	cout << text;
}
void Graphics::ClearScreen(void)
{
	SetColour(15, 0);
	for (int index = 0; index <= 200; index++)
	{
		DrawString(0, SCROLL_POS, "\n");
	}
}
void Graphics::SetColour(int fcolor, int bcolor)
{
	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) | fcolor)); // This will set colour of the console text and background
}
void Graphics::GameDisplay(Players& Player1, Players& Player2)
{
	//The following for loops will display the barrier around the GraphicalFront end
	for (int i = 0; i < 35; i++)
	{
		DrawString(20, i, "|");
	}
	for (int i = 36; i > 0; i--)
	{
		DrawString(174, i, "|");
	}
	DrawString(20, 35, "L");
	for (int i = 21; i < 175; i++)
	{
		DrawString(i, 35, "_");
	}
	for (int i = 0; i < 5; i++)
	{
		DrawString(5, 0, "*");
		DrawString(5, i, "|");
		DrawString(5, i, "|");
		DrawString(5, i, "|");
		DrawString(5, i, "|");
		DrawString(5, 5, "V");
	}
	ClearScreen();
	// The following DrawStrings will display the rules, UI
	
	DrawString(100, 20, "Rules of 501 Game");
	DrawString(100, 21, "_________________");
	DrawString(100, 22, "1:To win a a round(leg) you need to get you're score from 501 to 0!");
	DrawString(100, 23, "2:A match must end with either a double shot or bullseye!");
	DrawString(100, 24, "3:You're score should not be less than 0 or equivalent to one!");
	DrawString(100, 25, " 3.1:If broken, the last three shotsand the current score are retracted!");
	DrawString(100, 26, "4:To win a round(leg), the player's score must go from 501 to 0!");
	DrawString(100, 27, "5:To win the match, the player must win the majority of the sets!");
	DrawString(100, 28, "5:To win a set, the player must have won 5 legs!");

	DrawString(61, 1, "Name:"); cout << Player1.getName() << endl; DrawString(96, 1, "Name:"); cout << Player2.getName() << endl;
	DrawString(61, 2, "Score:"); cout << Player1.getScore() << " " << "\t\t\t\t" << "Score:" << Player2.getScore() << endl;
	DrawString(61, 3, "rate:"); cout << Player1.getRate() << "%" << "\t\t\t\t" << "rate:" << Player2.getRate() << "%" << endl;
	DrawString(61, 4, "Darts Thrown:"); cout << Player1.getDarts()<< " " << "\t\t\t" << "Darts Thrown:" << Player2.getDarts() << endl;
	DrawString(61, 5, "Legs:"); cout << Player1.getLegs() << "\t\t\t\t" << "Legs:" << Player2.getLegs() << endl;
	DrawString(61, 6, "Hits:"); cout << Player1.getHits() << "\t\t\t\t" << "Hits:" << Player2.getHits() << endl;
	DrawString(61, 7, "Misses:"); cout << Player1.getMisses() << "\t\t\t\t" << "Misses:" << Player2.getMisses() << endl;
	DrawString(61, 8, "Sets:"); cout << Player1.getSets() << "\t\t\t\t" << "Sets:" << Player2.getSets() << endl;
	DrawString(61, 9, "Win Frequency:"); cout << setprecision(3) << Player1.getMatchWinFrequncy() << "%" << "\t\t\t" << "Win frequency " << Player2.getMatchWinFrequncy() << "%" << endl;
	for (int i = 0; i < 9; i++)
	{
		SetColour((i + 1), 0);
		DrawString(61, (10 + i), "Dart Frequncy ");  cout << 8 + i << ":" << setprecision(3) << Player1.getDartFrequncy(i) << " %" << "\t\t" << "Dart Frequncy " << 8 + i << ": " << Player2.getDartFrequncy(i) << "%" << endl;
	}
	ClearScreen();
	SetColour(7, 0);
}
void Graphics::DartboardStatus(Players& Player)
{
	//This will display that the player is ready to start targeting
	SetColour(7, 7);
	DrawString(130, 0, "+---------------------------------+");
	DrawString(130, 1, "|                                 |");
	DrawString(130, 2, "|                                 |");
	DrawString(130, 3, "|                                 |");
	DrawString(130, 4, "|                                 |");
	DrawString(130, 5, "|                                 |");
	SetColour(0, 7);
	DrawString(130, 6, "             Ready                 ");
	SetColour(7, 7);
	DrawString(130, 7, "|                                 |");
	DrawString(130, 8, "|                                 |");
	DrawString(130, 9, "|                                 |");
	DrawString(130, 10,"|                                 |");
	DrawString(130, 11,"+---------------------------------+");
	SetColour(13, 0);
	
	if (Player.getHitOrMiss() == true) // If the Player's getHitorMiss does not equal false it will execute the following
	{
		if (Player.getDarts() > 0) // To make sure that the above Drawstring is executed, we have this IF statement in place to make sure
		{
			SetColour(2, 2);
			DrawString(130, 0, "+---------------------------------+");
			DrawString(130, 1, "|                                 |");
			DrawString(130, 2, "|                                 |");
			DrawString(130, 3, "|                                 |");
			DrawString(130, 4, "|                                 |");
			DrawString(130, 5, "|                                 |");
			SetColour(0, 2);
			DrawString(130, 6, "              Hit                  ");
			SetColour(2, 2);
			DrawString(130, 7, "|                                 |");
			DrawString(130, 8, "|                                 |");
			DrawString(130, 9, "|                                 |");
			DrawString(130, 10, "|                                 |");
			DrawString(130, 11, "+---------------------------------+");
			SetColour(13, 0);
		}
	}
	else
	{
		if (Player.getDarts() > 0)
		{
			SetColour(4, 4);
			DrawString(130, 0, "+---------------------------------+");
			DrawString(130, 1, "|                                 |");
			DrawString(130, 2, "|                                 |");
			DrawString(130, 3, "|                                 |");
			DrawString(130, 4, "|                                 |");
			DrawString(130, 5, "|                                 |");
			SetColour(0, 4);
			DrawString(130, 6, "              Miss                 ");
			SetColour(4, 4);
			DrawString(130, 7, "|                                 |");
			DrawString(130, 8, "|                                 |");
			DrawString(130, 9, "|                                 |");
			DrawString(130, 10, "|                                 |");
			DrawString(130, 11, "+---------------------------------+");
			SetColour(13, 0);
		}
	}
}