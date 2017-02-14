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

#include <set>

#include "Basic.h"

namespace Fengine
{
namespace Network
{
    class SocketPoller
    {
    public:
        SocketPoller();

        void AddSocket(const Socket &p_socket);
        void RemoveSocket(const Socket &p_socket);

        virtual int Poll(long p_time);

    protected:
        fd_set m_fdSet;
        fd_set m_activityFDSet;

        // linux平台需求。select需要传最大socket描述符+1作为参数，以便有最好轮询的效率。
        #ifndef _WIN32
        std::set<SOCK> m_socketDescs;
        #endif
    };



}   // end namespace Network

}   // end namespace Fengine