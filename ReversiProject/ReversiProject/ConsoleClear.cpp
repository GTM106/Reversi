#include "ConsoleClear.h"
#include <iostream>

void console_clear()
{
	//ANSI �G�X�P�[�v�R�[�h�𗘗p���ăR���\�[�����N���A����
	std::cout << "\x1B[2J\x1B[H";
}