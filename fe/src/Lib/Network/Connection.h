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
    const static int RECEIVE_BUFFER_SIZE = 2048;     // bytes.接收缓冲区。todo：可配置。
    const static int TIME_CHUNK = 16;                // second.监控在这个时间单位内客户端发送的数据量，不允许大于指定值，否则就是泛洪。

    template<class PROTOCOL>
    class Connection : public DataSocket
    {
    public:
        Connection();
        Connection(DataSocket &p_socket);

        void BufferData(const char* p_buffer, int p_size);
        void SendBuffer();
        void Receive();

        sint64 GetLastSendTime() const;

        int GetLastDataRate() const
        {
            return m_lastDatarate;
        }

        int GetCurrentDataRate() const
        {
            return m_receivedDataBytes / TIME_CHUNK;
        }

        int GetBufferedBytes() const
        {
            return (int)m_sendBuffer.size();
        }

        sint64 GetCreationTime() const
        {
            return m_creationTime;
        }

        bool Closed()
        {
            return m_closed;
        }

        PROTOCOL& Protocol() 
        { 
            return m_protocol; 
        }

        typename PROTOCOL::HANDLER *Handler()
        {
            if (m_handlerstack.size() == 0)
            {
                return 0;
            }

            return m_handlerstack.top();
        }

        void AddHandler(typename PROTOCOL::HANDLER *p_handler)
        {
            if (Handler())
            {
                Handler()->Leave();
            }
            m_handlerStack.push(p_handler);
            p_handler->Enter();
        }

        void RemoveHandler()
        {
            Handler()->Leave();
            delete Handler();
            m_handlerStack.pop();
            if (Handler())
            {
                Handler()->Enter();
            }
        }

        void SwitchHandler(typename PROTOCOL::HANDLER *p_handler)
        {
            if (Handler())
            {
                Handler()->Leave();
                delete Handler();
                m_handlerStack.pop();
            }
            m_handlerStack.push(p_handler);
            p_handler->Enter();
        }

        void ClearHandlers()
        {
            if (Handler())
            {
                Handler()->Leave();
            }

            while (Handler())
            {
                delete Handler();
                m_handlerStack.pop();
            }
        }

        void CloseSocket()
        {
            DataSocket::Close();

            ClearHandlers();
        }

    private:
        void Initialize();

    protected:
        PROTOCOL m_protocol;

        std::string m_sendBuffer;
        char m_receiveBuffer[RECEIVE_BUFFER_SIZE];

        std::stack<typename PROTOCOL::HANDLER *> m_handlerStack;

        sint64 m_creationTime;      // 连接创建时间，毫秒
        int m_receivedDataBytes;    // 当前计算周期内收到的数据量
        int m_lastDatarate;         // 上一个计算周期数据传输率
        sint64 m_lastReceiveTime;   // 最后一次接收数据时间，秒
        sint64 m_lastSendTime;      // 最后一次发送数据时间，秒
        bool m_hasSendFailed;       // 上次是否发送失败

        bool m_closed;              // 连接是否被关闭
    };


    // ----------------------------------------------------------------------------------
    template<class PROTOCOL>
    Connection<PROTOCOL>::Connection()
    {
        Initialize();
    }

    template<class PROTOCOL>
    Connection<PROTOCOL>::Connection(DataSocket &p_socket)
        :DataSocket(p_socket),
    {
        Initialize();
    }

    template<class PROTOCOL>
    void Connection<PROTOCOL>::Initialize()
    {
        sint64 m_creationTime = GetTimeMS();
        int m_receivedDataBytes = 0;
        int m_lastDatarate = 0;
        sint64 m_lastReceiveTime = 0;
        sint64 m_lastSendTime = 0;
        bool m_hasSendFailed = false;

        bool m_closed = false;
    }

    template<class PROTOCOL>
    void Connection<PROTOCOL>::BufferData(const char *p_buffer, int p_size)
    {
        m_sendBuffer.append(p_buffer, p_size);
    }

    template<class PROTOCOL>
    void Connection<PROTOCOL>::SendBuffer()
    {
        if (m_sendBuffer.size() > 0)
        {
            int sentNum = Send(m_sendBuffer.data(), (int)m_sendBuffer.size());
            if (sentNum > 0)
            {
                m_sendBuffer.erase(0, sentNum);
                m_lastSendTime = GetTimeS();
                m_hasSendFailed = false;    // 有可能上次失败
            }
            else
            {
                if (!m_hasSendFailed)
                {
                    m_hasSendFailed = true;
                    m_lastSendTime = GetTimeS();
                }
                // 如果上次已失败则不更新发送时间，当阻塞时间超出合理值，连接会被关闭。
            }
        }
        // 没有数据发送则什么都不做。如果上次发送成功则m_hasSendFailed为false，不会导致连接被关闭。
    }

    template<class PROTOCOL>
    void Connection<PROTOCOL>::Receive()
    {
        int bytes = DataSocket::Receive(m_receiveBuffer, RECEIVE_BUFFER_SIZE);

        sint64 t = GetTimeS();
        // 商不相等，进入了下一个统计周期，重置相关数据
        if (m_lastReceiveTime / TIME_CHUNK != t / TIME_CHUNK)
        {
            m_lastDatarate = m_receivedDataBytes / TIME_CHUNK;
            m_receivedDataBytes = 0;
            m_lastReceiveTime = t;
        }
        m_receivedDataBytes += bytes;

        m_protocol.Translate(*this, m_receiveBuffer, bytes);
    }

    template<class PROTOCOL>
    sint64 Connection<PROTOCOL>::GetLastSendTime() const
    {
        if (m_hasSendFailed)
        {
            return GetTimeS() - m_lastSendTime;
        }

        return 0;
    }

}   // end namespace Network

}   // end namespace Fengine




#endif  // __CONNECTION_H__