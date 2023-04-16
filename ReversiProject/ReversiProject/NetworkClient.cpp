#include "NetworkClient.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define BUFFER_LEN 1000
#define MY_PORT_NUM 55555
#define SERVER_IP "localhost"

#include <iostream>
#include <winsock2.h>
#include "NetworkReversi.h"
#include "ConsoleManager.h"

using namespace std;

NetworkClient::~NetworkClient()
{
}

void NetworkClient::networkStart()
{
	char buffer[BUFFER_LEN];

	//�|�[�g�ԍ���IP�A�h���X�̏�����
	unsigned short portNum = MY_PORT_NUM;
	char serverIP[] = SERVER_IP;

	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (result)
	{
		cout << "WSAStartup�̎��s�B\n";
		return;
	}

	SOCKET soc = socket(AF_INET, SOCK_STREAM, 0);
	if (soc < 0)
	{
		cout << "�\�P�b�g�I�[�v���G���[\n";
		WSACleanup();
		return;
	}

	HOSTENT* lpHost = gethostbyname(serverIP);
	if (lpHost == NULL)
	{
		unsigned int addr = inet_addr(serverIP);
		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);

		//��������s������G���[�Ƃ��ĕԂ�
		if (lpHost == NULL)
		{
			cout << "gethostbyaddr�̃G���[\n";
			closesocket(soc);
			WSACleanup();
			return;
		}
	}

	SOCKADDR_IN saddr;
	ZeroMemory(&saddr, sizeof(SOCKADDR_IN));
	saddr.sin_family = lpHost->h_addrtype;
	saddr.sin_port = htons(portNum);
	saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);
	if (connect(soc, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		cout << "�ΐ푊�肪������܂���ł����B" << endl;
		closesocket(soc);
		WSACleanup();
		return;
	}

	cout << "�ΐ푊�肪������܂����I" << endl;

	NetworkReversi reversi(Client);

	while (1)
	{
		cout << "�ΐ푊�肪�v�l���ł��c�c" << endl;
		int rcv = recv(soc, buffer, sizeof(buffer) - 1, 0);
		if (rcv == SOCKET_ERROR)
		{
			cout << "�G���[�ł��B" << endl;
			break;
		}
		buffer[rcv] = '\0';

		if (strcmp(buffer, "--") == 0)
		{
			cout << "�ΐ푊�肪�ސȂ��܂����B" << endl;
			break;
		}
		if (strcmp(buffer, "//") == 0)break;

		reversi.enemyTurn(Client, string(buffer));

		Vector2Int pos = reversi.playerTurn(Client);
		buffer[0] = pos.x + '0';
		buffer[1] = pos.y + '0';
		buffer[2] = '\0';

		send(soc, buffer, 2, 0);

		if (strcmp(buffer, "--") == 0)break;
		if (strcmp(buffer, "//") == 0)break;
	}

	shutdown(soc, SD_BOTH);
	closesocket(soc);

	result = WSACleanup();
	if (result)
	{
		cout << "WSACleanup�̎��s�B\n";
		return;
	}
}