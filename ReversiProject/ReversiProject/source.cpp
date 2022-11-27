#include "Reversi.h"
#include "ConsoleManager.h"

int main()
{
	Reversi reversi;
	ConsoleManager consoleManager;

	consoleManager.setConsoleCursorErase();
	reversi.start();
}