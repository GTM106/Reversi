#pragma once

class INetworkStarter
{
public:
	virtual ~INetworkStarter() {}
	virtual	void networkStart() = 0;
};