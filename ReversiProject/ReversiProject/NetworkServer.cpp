#include "NetworkServer.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define BUFFER_LEN 100
#define MY_PORT_NUM 55555

#include <iostream>
#include <winsock2.h>
#include "NetworkReversi.h"

using namespace std;

NetworkServer::~NetworkServer()
{
}

void NetworkServer::networkStart()
{
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (result)
	{
		cout << "WSAStartup�̎��s�B" << endl;
		return;
	}

	SOCKET listenSoc = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSoc < 0)
	{
		cout << "�\�P�b�g�I�[�v���G���[" << endl;
		WSACleanup();
		return;
	}

	SOCKADDR_IN saddr;
	ZeroMemory(&saddr, sizeof(SOCKADDR_IN));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(MY_PORT_NUM);
	saddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(listenSoc, (struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		cout << "bind�̃G���[" << endl;
		closesocket(listenSoc);
		WSACleanup();
		return;
	}

	if (listen(listenSoc, 0) == SOCKET_ERROR)
	{
		cout << "listen error." << endl;
		closesocket(listenSoc);
		WSACleanup();
		return;
	}

	cout << "�ΐ푊���ҋ@���ł��c" << endl;

	SOCKADDR_IN from;
	int fromlen = sizeof(from);
	SOCKET soc = accept(listenSoc, (SOCKADDR*)&from, &fromlen);
	if (soc == INVALID_SOCKET)
	{
		cout << "accept error." << endl;
		closesocket(listenSoc);
		WSACleanup();
		return;
	}
	cout << "�ΐ푊�肪������܂����I" << endl;

	closesocket(listenSoc);

	NetworkReversi reversi(Host);
	char buffer[BUFFER_LEN];

	while (1)
	{
		Vector2Int pos = reversi.playerTurn(Host);
		buffer[0] = pos.x + '0';
		buffer[1] = pos.y + '0';
		buffer[2] = '\0';

		send(soc, buffer, int(strlen(buffer)), 0);

		if (strcmp(buffer, "--") == 0)break;
		if (strcmp(buffer, "//") == 0)break;

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

		reversi.enemyTurn(Host, string(buffer));
	}

	shutdown(soc, SD_BOTH);
	closesocket(soc);

	result = WSACleanup();
	if (result)
	{
		cout << "WSACleanup�̎��s" << endl;
		return;
	}
}