/*
This source file is part of Fengine
For the latest info, see

Copyright (c) 2017 Fengine.

Fengine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fengine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Fengine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NetworkTypes.h"

namespace Fengine
{

namespace Network
{

	class Socket
	{
	public:
		void SetBlocking(bool p_blockMode);

		void Close();

		SOCK GetSock() const
		{
			return m_sock;
		}

		PORT GetLocalPort() const
		{
			return ntohs( m_localInfo.sin_port );
		}

		IP_ADDRESS GetLocalAddress() const
		{
			return m_localInfo.sin_addr.s_addr;
		}
	protected:
		Socket(SOCK p_socket = -1);	// Socket基类不允许实例化

		SOCK m_sock;
		bool m_isBlocking;
		struct sockaddr_in m_localInfo;
	};


	class DataSocket : public Socket
	{
	public:
		DataSocket(SOCK p_socket);

		void Connect( IP_ADDRESS p_addr, PORT p_port );
		int Send( const char *p_buffer, int p_size );
		int Receive( char *p_buffer, int p_size );

		void Close();

		IP_ADDRESS GetRemoteAddress() const
		{
			return m_remoteInfo.sin_addr.s_addr;
		}

		PORT GetRemotePort() const
		{
			return m_remoteInfo.sin_port;
		}
	protected:
		bool m_connected;

		struct sockaddr_in m_remoteInfo;
	};

    class ListeningSocket : public Socket
    {

    };

}	// end namespace Network

}	// end namespace Fengine


#endif  // __SOCKET_H__