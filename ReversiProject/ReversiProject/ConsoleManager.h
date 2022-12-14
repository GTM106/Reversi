#pragma once
#include <Windows.h>

//     色定義
#define     COL_BLACK   0x00
#define     COL_DARK_BLUE       0x01
#define     COL_DARK_GREEN 0x02
#define     COL_DARK_CYAN       0x03
#define     COL_DARK_RED     0x04
#define     COL_DARK_VIOLET0x05
#define     COL_DARK_YELLOW   0x06
#define     COL_GRAY 0x07
#define     COL_LIGHT_GRAY      0x08
#define     COL_BLUE     0x09
#define     COL_GREEN   0x0a
#define     COL_CYAN     0x0b
#define     COL_RED      0x0c
#define     COL_VIOLET  0x0d
#define     COL_YELLOW 0x0e
#define     COL_WHITE   0x0f
#define     COL_INTENSITY     0x08     // 高輝度マスク
#define     COL_RED_MASK     0x04     // 赤色ビット
#define     COL_GREEN_MASK 0x02     // 緑色ビット
#define     COL_BLUE_MASK   0x01     //  青色ビット

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
	void resetConsoleColor();
	void setConsoleCursorErase();
	void setColor(int fg, int bg);
	void setColor(int fg);
};