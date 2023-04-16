#pragma once
#include <memory>
#include "INetworkStarter.h"

class NetworkStarter
{
	std::unique_ptr<INetworkStarter> networkStart;

public:
	void start();
};

