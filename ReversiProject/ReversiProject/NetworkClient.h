#pragma once
#include "INetworkStarter.h"

class NetworkClient : public INetworkStarter
{
	~NetworkClient();

	// INetworkStarter ����Čp������܂���
	virtual void networkStart() override;
};