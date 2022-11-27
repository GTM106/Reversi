#include "ConsoleManager.h"
#include <iostream>

ConsoleManager::ConsoleManager()
{
	getConsoleCursorInfo();
	getConsoleScreenBufferInfo();
}

void ConsoleManager::console_clear()
{
	//ANSI エスケープコードを利用してコンソールをクリアする
	std::cout << "\x1B[2J\x1B[H";
}

void ConsoleManager::getConsoleScreenBufferInfo()
{
	GetConsoleScreenBufferInfo(handle, &csbi);
}

void ConsoleManager::getConsoleCursorInfo()
{
	GetConsoleCursorInfo(handle, &cci);
}

//背景色をグレーにする
void ConsoleManager::setConsoleBackGray()
{
	SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

//もとに戻す。※事前に元の色の取得が必要
void ConsoleManager::resetConsoleColor()
{
	SetConsoleTextAttribute(handle, csbi.wAttributes);
}

//カーソルを消す
void ConsoleManager::setConsoleCursorErase()
{
	// メンバ変数であるbVisibleがカーソルの表示・非表示を制御する変数なので、これをFALSEにする事でカーソルを非表示にできる
	cci.bVisible = FALSE;

	// 変更した構造体情報をコンソールWindowにセットする
	SetConsoleCursorInfo(handle, &cci);
}

void ConsoleManager::setColor(int col)
{
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attr = 0;
	if (col & COL_INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if (col & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if (col & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (col & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;
	SetConsoleTextAttribute(hCons, attr);
}

void ConsoleManager::setColor(int fg, int bg)
{
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attr = 0;
	if (fg & COL_INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if (fg & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if (fg & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (fg & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;

	if (bg & COL_INTENSITY)
		attr |= BACKGROUND_INTENSITY;
	if (bg & COL_RED_MASK)
		attr |= BACKGROUND_RED;
	if (bg & COL_GREEN_MASK)
		attr |= BACKGROUND_GREEN;
	if (bg & COL_BLUE_MASK)
		attr |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(hCons, attr);
}
