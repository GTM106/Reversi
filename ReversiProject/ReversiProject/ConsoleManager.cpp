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
void ConsoleManager::setConsoleBackBlack()
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