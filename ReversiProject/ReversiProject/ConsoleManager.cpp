#include "ConsoleManager.h"
#include <iostream>

ConsoleManager::ConsoleManager()
{
	getConsoleCursorInfo();
	getConsoleScreenBufferInfo();
}

void ConsoleManager::console_clear()
{
	//ANSI �G�X�P�[�v�R�[�h�𗘗p���ăR���\�[�����N���A����
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

//�w�i�F���O���[�ɂ���
void ConsoleManager::setConsoleBackGray()
{
	SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

//���Ƃɖ߂��B�����O�Ɍ��̐F�̎擾���K�v
void ConsoleManager::resetConsoleColor()
{
	SetConsoleTextAttribute(handle, csbi.wAttributes);
}

//�J�[�\��������
void ConsoleManager::setConsoleCursorErase()
{
	// �����o�ϐ��ł���bVisible���J�[�\���̕\���E��\���𐧌䂷��ϐ��Ȃ̂ŁA�����FALSE�ɂ��鎖�ŃJ�[�\�����\���ɂł���
	cci.bVisible = FALSE;

	// �ύX�����\���̏����R���\�[��Window�ɃZ�b�g����
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
