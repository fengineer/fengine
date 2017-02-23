#ifndef __TELNET_LOGON_H__
#define __TELNET_LOGON_H__

#include <string>
#include <iostream>
#include "Network.h"

namespace Fengine
{
namespace Network
{
	class TelnetLogon : public ConnectionHandler< Telnet, std::string >
	{
		typedef Connection<Telnet> CONNECTION;
        const std::string END_STRING = "\r\n";
	public:
		TelnetLogon(CONNECTION &p_conn)
			:ConnectionHandler<Telnet, std::string>(p_conn)
		{}

		virtual void Enter()
		{
			std::cout << "TelnetLogon::Enter." << std::endl;
			std::string cb = "wellcome to fengine server..." + END_STRING;
			m_connection->BufferData(cb.c_str(), (int)cb.size());
		}

		virtual void Leave()
		{
			std::cout << "TelnetLogon::Leave.bye bye." << std::endl;
		}

		virtual void Handle(std::string p_data)
		{
			std::cout << "TelnetLogon::Handle:" << p_data << std::endl;
			std::string cb = "handle str:" + p_data + END_STRING;
			m_connection->BufferData(cb.c_str(), (int)cb.size());
			if (p_data == "q" || p_data == "Q")
			{
				m_connection->Close();
			}
		}

		virtual void Hungup()
		{
			std::cout << "TelnetLogon::Hungup." << std::endl;
		}

		virtual void Flooded()
		{
			std::cout << "TelnetLogon::Flooded." << std::endl;
		}

		static void NoRoom(CONNECTION &p_conn)
		{
			std::cout << "TelnetLogon::NoRoom." << std::endl;
		}
	};


}	// end namespace Network

}	// end namespace Fengine

#endif // __TELNET_LOGON_H__