#pragma once
#include "INetworkStarter.h"

class NetworkServer : public INetworkStarter
{
	~NetworkServer();

	// INetworkStarter を介して継承されました
	virtual void networkStart() override;
};