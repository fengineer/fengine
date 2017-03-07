
#include "Common.h"

#include <stdio.h>
#include <iostream>

#include "Network.h"
#include "Thread.h"
#include "TelnetLogon.h"

using namespace Fengine;

int main(int argc, char *argv[])
{
	Fengine::uint64 passMS = Fengine::GetTimeMS();
	std::cout << "passMS:" << passMS << std::endl;
	std::cout << "passMinuts:" << Fengine::GetTimeM() << std::endl;

	Network::ConnectionMgr<Network::Telnet, Network::TelnetLogon> connMgr;
	Network::ListenMgr<Network::Telnet, Network::TelnetLogon> listenMgr;
	listenMgr.SetConnectionMgr(connMgr);
	listenMgr.AddListenPort(20023);

	while (true)
	{
		listenMgr.Listen();
		connMgr.Manage();

		Thread::YieldThread(2000);
	}

	getchar();
	return 0;
}
