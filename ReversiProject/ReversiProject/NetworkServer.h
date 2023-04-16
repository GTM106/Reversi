#pragma once
#include "INetworkStarter.h"

class NetworkServer : public INetworkStarter
{
	~NetworkServer();

	// INetworkStarter ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void networkStart() override;
};