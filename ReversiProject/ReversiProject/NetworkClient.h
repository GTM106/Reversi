#pragma once
#include "INetworkStarter.h"

class NetworkClient : public INetworkStarter
{
	~NetworkClient();

	// INetworkStarter を介して継承されました
	virtual void networkStart() override;
};