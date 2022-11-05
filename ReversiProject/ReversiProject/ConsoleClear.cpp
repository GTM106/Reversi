#include "ConsoleClear.h"
#include <iostream>

void console_clear()
{
	//ANSI エスケープコードを利用してコンソールをクリアする
	std::cout << "\x1B[2J\x1B[H";
}