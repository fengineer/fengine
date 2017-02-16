/*
This source file is part of Fengine
For the latest info, see <https://github.com/imgamer/fengine/>.

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

#ifndef __CONNECTION_MGR_H__
#define __CONNECTION_MGR_H__

#include <list>

#include "Socket.h"
#include "Connection.h"

namespace Fengine
{
namespace Network
{
	template<typename PROTOCOL, typename HANDLER>
	class ConnectionMgr
	{
		typedef std::list<Connection<PROTOCOL>> CONNECTION_LIST;
		typedef typename CONNECTION_LIST::iterator CONNECTION_LIST_ITER;

	public:
		ConnectionMgr(nt p_maxDatarate = 1024,		// 1 kbytes
						int p_sendTimeout = 60,		// 60 seconds
						int p_maxBuffered = 8192);	// 8 kbytes

		~ConnectionMgr();

		void NewConnection(DataSocket &p_socket);

		int AvailableConnections()
		{
			return MAX_FD_SIZE - (int)( m_connections.size() );
		}

		int TotalConnections()
		{
			return (int)( m_connections.size() );
		}
	protected:
		CONNECTION_LIST m_connections;

		int m_maxDatarate;
    	int m_sendTimeout;
	    int m_maxBuffered;

	};

	// -------------------------------------------------
	template<typename PROTOCOL, typename HANDLER>
	ConnectionMgr<PROTOCOL, HANDLER>::
		ConnectionMgr(int p_maxDatarate = 1024,
						int p_sendTimeout = 60,
						int p_maxBuffered = 8192)
		:m_maxDatarate(p_maxDatarate),
		m_sendTimeout(p_sendTimeout),
		m_maxBuffered(p_maxBuffered)
	{
	}

	template<typename PROTOCOL, typename HANDLER>
		ConnectionMgr<PROTOCOL, HANDLER>::
			~ConnectionMgr()
	{
		CONNECTION_LIST_ITER iter = m_connections.begin();
		for(; iter != m_connections.end; iter++)
		{
			iter->CloseSocket();
		}
	}

	template<typename PROTOCOL, typename HANDLER>
	void ConnectionMgr<PROTOCOL, HANDLER>::NewConnection(DataSocket &p_socket)
	{
		Connection<PROTOCOL> conn(p_socket);
		if(AvailableConnections)
		{
			m_connections.push_back(conn);

			Connection<PROTOCOL> &conn2 = *m_connections.rbegin();
			conn2.SetBlocking(false);
			conn2.AddHandler(new HANDLER(conn2);
		}
		else
		{
			 HANDLER::NoRoom(conn);
			 conn.CloseSocket();
		}
	}


}	// end namespace Network

}	// end namespace Fengine



#endif // __CONNECTION_MGR_H__