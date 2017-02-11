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

#include "Socket.h"

namespace Fengine
{

namespace Network
{
	Socket::Socket(sock p_socket)
		:m_sock(p_socket),
		m_isBlocking(true)
	{
		if(m_sock != -1)
		{
			socklen_t len = sizeof(m_localInfo);
			getsockname(m_sock, (sockaddr *)&m_localInfo, &len);
		}
	}

	void SetBlocking(bool p_isBlocking)
	{
		int err;
		#ifdef _WIN32
			// todo
		#else
		#endif
	}

	void Socket::Close()
	{
		#ifdef _WIN32
			closesocket(m_sock);
		#else
			close(m_sock);
		#endif

		m_sock = -1;
	}
}	// end namespace Network


}	// end namespace Network