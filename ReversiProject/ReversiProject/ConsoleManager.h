#pragma once
#include <Windows.h>

class ConsoleManager
{
public:
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO cci;

	ConsoleManager();

	void getConsoleScreenBufferInfo();
	void getConsoleCursorInfo();
	void console_clear();
	void setConsoleBackGray();
	void setConsoleBackBlack();
	void setConsoleCursorErase();
};