#pragma once
#include "INetworkStarter.h"

class NetworkServer : public INetworkStarter
{
	~NetworkServer();

	// INetworkStarter ����Čp������܂���
	virtual void networkStart() override;
};