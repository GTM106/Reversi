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
void ConsoleManager::setConsoleBackBlack()
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