#include "NetworkStarter.h"
#include "ConsoleManager.h"
#include "NetworkServer.h"
#include "NetworkClient.h"
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_2 50
#define KEY_4 52
#define KEY_6 54
#define KEY_8 56
#define KEY_U 117
#define KEY_TAB 9
#define KEY_ESC 27

using namespace std;

void NetworkStarter::start()
{
	ConsoleManager consoleManager;
	consoleManager.setConsoleCursorErase();

	bool isHost = true;
	int val = -1;
	cout << "�ǂ���Őڑ����܂����H" << endl;
	if (isHost)cout << "��";
	cout << "�@�@�z�X�g" << endl;
	if (!isHost)cout << "��";
	cout << "�@�@�N���C�A���g" << endl;

	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
			//��
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (isHost)continue;
			isHost = true;
			break;
			//��
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (!isHost)continue;
			isHost = false;
			break;
			//����
		case KEY_ENTER:
			break;
		default:
			continue;
		}

		consoleManager.console_clear();

		cout << "�ǂ���Őڑ����܂����H" << endl;
		if (isHost)cout << "��";
		cout << "�@�@�z�X�g" << endl;
		if (!isHost)cout << "��";
		cout << "�@�@�N���C�A���g" << endl;
	}

	if (isHost) networkStart.reset(new NetworkServer());
	else networkStart.reset(new NetworkClient());

	networkStart->networkStart();
}
