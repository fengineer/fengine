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

#include "SocketPoller.h"

namespace Fengine
{
namespace Network
{
    SocketPoller::SocketPoller()
    {
        FD_ZERO(&m_fdSet);
        FD_ZERO(&m_activityFDSet);
    }

    void SocketPoller::AddSocket(const Socket &p_socket)
    {
        FD_SET(p_socket.GetSock(), &m_fdSet);

        #ifndef _WIN32
            m_socketDescs.insert(p_socket.GetSock());
        #endif
    }

    void SocketPoller::RemoveSocket(const Socket &p_socket)
    {
        FD_CLR(p_socket.GetSock(), &m_fdSet);

        #ifndef _WIN32
            m_socketDescs.erase(p_socket.GetSock());
        #endif
    }

    int SocketPoller::Poll(long p_time)
    {
        //if (m_fdSet.fd_count == 0)
        //{
        //    return 0;
        //}
        struct timeval tval = { 0, p_time*1000 };
        m_activityFDSet = m_fdSet;

        #ifdef _WIN32
            return select(0, &m_activityFDSet, 0, 0, &tval);
        #else
            if (m_socketDescs.size() == 0)
                return 0;
            return select(*(m_socketDescs.rbegin()), &m_activityFDSet, 0, 0, &tval);
        #endif
    }

}   // end namespace Network

}   // end namespace Fengine
