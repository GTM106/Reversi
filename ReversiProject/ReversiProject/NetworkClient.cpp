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

	//ポート番号とIPアドレスの初期化
	unsigned short portNum = MY_PORT_NUM;
	char serverIP[] = SERVER_IP;

	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (result)
	{
		cout << "WSAStartupの失敗。\n";
		return;
	}

	SOCKET soc = socket(AF_INET, SOCK_STREAM, 0);
	if (soc < 0)
	{
		cout << "ソケットオープンエラー\n";
		WSACleanup();
		return;
	}

	HOSTENT* lpHost = gethostbyname(serverIP);
	if (lpHost == NULL)
	{
		unsigned int addr = inet_addr(serverIP);
		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);

		//これも失敗したらエラーとして返す
		if (lpHost == NULL)
		{
			cout << "gethostbyaddrのエラー\n";
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
		cout << "対戦相手が見つかりませんでした。" << endl;
		closesocket(soc);
		WSACleanup();
		return;
	}

	cout << "対戦相手が見つかりました！" << endl;

	NetworkReversi reversi(Client);

	while (1)
	{
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
		cout << "WSACleanupの失敗。\n";
		return;
	}
}