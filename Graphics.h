#pragma once
#include <iostream>
#include <Windows.h>
#include "Players.h" 
#include <iomanip>
#define SCROLL_POS 24
using namespace std;
class Graphics
{	
public:
	~Graphics();
	CONSOLE_SCREEN_BUFFER_INFO con_info;   // holds screen info 
	HANDLE hconsole;         // handle to console 
	void initiate_Graphics(); // This initizates the Graphics, that will be used throughout the program
	void DrawString(int x_axis, int y_axis, string text); //This function will draw the text, that we need
	void ClearScreen(void);
	void SetColour(int fcolor, int bcolor); // This function will set the colour of the text and background
	void GameDisplay(Players& Player1, Players& Player2); //This function will display the Graphical front end
	void DartboardStatus(Players& Player); //This will draw the Dartboard status, to show if the player hit the board or missed the board

};

