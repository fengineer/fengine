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

#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <stack>
#include <string>

#include "Basic.h"
#include "Socket.h"


namespace Fengine
{
namespace Network
{
    const static int RECEIVE_BUFFER_SIZE = 1024;     // bytes.接收缓冲区。todo：可配置。
    const static int TIME_CHUNK = 16;                // second.监控在这个时间单位内客户端发送的数据量，不允许大于指定值，否则就是泛洪。

    template<class Protocol>
    class Connection : public DataSocket
    {
    public:
        Connection();
        Connection(DataSocket &p_socket);

        void BufferData(const char* p_buffer, int p_size);
        void SendBuffer();
        void Receive();

    private:
        void Initialize();

    protected:
        Protocol m_protocol;

        std::string m_sendBuffer;
        char m_receiveBuff[RECEIVE_BUFFER_SIZE];

        std::stack<typename Protocol::HANDLER *> m_handlerStack;

        sint64 m_creationTime;      // 连接创建时间
        int m_datarate;             // 即时数据传输率
        int m_lastDatarate;         // 上一个计算周期数据传输率
        sint64 m_lastReceiveTime;   // 最后一次接收数据时间
        sint64 m_lastSendTime;      // 最后一次发送数据时间
        bool m_hasSendFailed;       // 上次是否发送失败

        bool m_closed;              // 连接是否被关闭
    };


    // ----------------------------------------------------------------------------------
    template<class Protocol>
    Connection<Protocol>::Connection()
    {
        Initialize();
    }

    template<class Protocol>
    Connection<Protocol>::Connection(DataSocket &p_socket)
        :DataSocket(p_socket),
    {
        Initialize();
    }

    template<class Protocol>
    void Connection<Protocol>::Initialize()
    {
        sint64 m_creationTime = GetTimeMS();
        int m_datarate = 0;
        int m_lastDatarate = 0;
        sint64 m_lastReceiveTime = 0;
        sint64 m_lastSendTime = 0;
        bool m_hasSendFailed = false;

        bool m_closed = false;
    }


}   // end namespace Network

}   // end namespace Fengine




#endif  // __CONNECTION_H__