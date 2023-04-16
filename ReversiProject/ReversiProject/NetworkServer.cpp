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
		cout << "WSAStartupの失敗。" << endl;
		return;
	}

	SOCKET listenSoc = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSoc < 0)
	{
		cout << "ソケットオープンエラー" << endl;
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
		cout << "bindのエラー" << endl;
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

	cout << "対戦相手を待機中です…" << endl;

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
	cout << "対戦相手が見つかりました！" << endl;

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

		cout << "対戦相手が思考中です……" << endl;
		int rcv = recv(soc, buffer, sizeof(buffer) - 1, 0);
		if (rcv == SOCKET_ERROR)
		{
			cout << "エラーです。" << endl;
			break;
		}
		buffer[rcv] = '\0';

		if (strcmp(buffer, "--") == 0)
		{
			cout << "対戦相手が退席しました。" << endl;
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
		cout << "WSACleanupの失敗" << endl;
		return;
	}
}