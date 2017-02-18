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

#ifndef __LISTEN_MGR_H__
#define __LISTEN_MGR_H__

#include <vector>
#include "NetworkTypes.h"
#include "Socket.h"
#include "SocketPoller.h"
#include "NetworkErrors.h"
#include "ConnectionMgr.h"


namespace Fengine
{
namespace Network
{
	template<typename PROTOCOL, typename DefaultHandler>
	class ListenMgr
	{
	public:
		ListenMgr();
		~ListenMgr();

		void AddListenPort(PORT p_port);

		void SetConnectionMgr(ConnectionMgr<PROTOCOL, DefaultHandler> &p_connMgr);

		void Listen();
	protected:
		std::vector<ListenSocket> m_listenSockets;

		SocketPoller m_poller;

		ConnectionMgr<PROTOCOL, DefaultHandler> *m_connectionMgr;
	};

	// ----------------------------------------------------------------
	template<typename PROTOCOL, typename DefaultHandler>
	ListenMgr<PROTOCOL, DefaultHandler>::
		ListenMgr()
		:m_listenSockets(),
		m_poller(),
		m_connectionMgr(NULL)
	{

	}

	template<typename PROTOCOL, typename DefaultHandler>
	ListenMgr<PROTOCOL, DefaultHandler>::
		~ListenMgr()
	{
		for(size_t i = 0; i < m_listenSockets.size(), i++)
		{
			m_listenSockets[i].Close();
		}
	}

	template<typename PROTOCOL, typename DefaultHandler>
	void ListenMgr<PROTOCOL, DefaultHandler>::
		AddListenPort(PORT p_port)
	{
		if ((int)m_listenSockets.size() >= MAX_FD_SIZE)
		{
			throw( Exception(ESocketLimitReached) );
		}

		ListenSocket ls = ListenSocket();
		ls.Listen(p_port);
		ls.SetBlocking(false);

		m_listenSockets.push_back(ls);

		m_poller.AddSocket(ls);
	}

	template<typename PROTOCOL, typename DefaultHandler>
	void ListenMgr<PROTOCOL, DefaultHandler>::
		SetConnectionMgr(ConnectionMgr<PROTOCOL, DefaultHandler> &p_connMgr)
	{
		m_connectionMgr = &p_connMgr;
	}

	template<typename PROTOCOL, typename DefaultHandler>
	void ListenMgr<PROTOCOL, DefaultHandler>::
		Listen()
	{
		if(m_poller.Poll() > 0)
		{
			for(size_t i = 0; i < m_listenSockets.size(); i++)
			{
				if(m_poller.HasActivity(m_listenSockets[i]))
				{
					try
					{
						DataSocket dsocket = m_sockets[i].Accept();

						m_connectionMgr->NewConnection(dsocket);
					}
					// 仅过滤EOperationWouldBlock异常，这是为了防止连接欺骗（connection exploit）
					// SetBlocking是设置了非阻塞，但是遇到阻塞（没读到数据）会抛出EOperationWouldBlock（经过转换的）异常。
					catch (Exception& e)
					{
						// 只过滤阻塞错误
						if (e.ErrorCode() != EOperationWouldBlock)
						{
							throw e;
						}
					}
				}
			}
		}
	}

}	// end namespace Network

}	// end namespace Fengine

#endif // __LISTEN_MGR_H__