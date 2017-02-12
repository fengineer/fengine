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
	Socket::Socket(SOCK p_socket)
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
			unsigned long mode = !p_isBlocking;	// 与本函数相反的语义
			err = ioctlsocket(m_sock, FIONBIO, &mode);
		#else
			int flags = fcntl(m_sock, F_GETFL, 0);
			if(p_isBlocking == false)
            {
                flags |= O_NONBLOCK;
            }
            else
            {
                flags &= ~O_NONBLOCK;
            }
            err = fcntl( m_sock, F_SETFL, flags );
		#endif
        if(err == -1)
        {
        	throw(Exception(GetError()));
        }

        m_isBlocking = p_isBlocking;
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


	// ------------------------------------------------------------
	DataSocket::DataSocket(SOCK p_socket)
		:Socket(p_socket),
		m_connected(false),
		m_remoteInfo()
	{
		if(p_socket != -1)
		{
			socklen_t len = sizeof(m_remoteInfo);
			int err = getpeername(p_socket, (struct sockaddr *)&m_remoteInfo, &len);
			if(err == -1)
			{
				throw( Exception(GetError()) );
			}
			m_connected = true;
		}
	}

	void DataSocket::Connect(IP_ADDRESS p_addr, PORT p_port)
    {
        if(m_connected)
        {
            throw(Exception(EAlreadyConnected));
        }

        if(m_sock == -1)
        {
        	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        	if(m_sock == -1)
        	{
        		throw(Exception(GetError()));
        	}
        }

        // set up the socket address structure
        m_remoteinfo.sin_family = AF_INET;
        m_remoteinfo.sin_port = htons( p_port );
        m_remoteinfo.sin_addr.s_addr = p_addr;
        memset( &(m_remoteinfo.sin_zero), 0, 8 );

        int err;
        socklen_t len = sizeof(struct sockaddr);
        err = connect(m_sock, (struct sockaddr *)&m_remoteinfo, len);
        if(err == -1)
        {
        	throw( Exception( GetError() ) );
        }
        m_connected = true;

        err = getsockname(m_sock, (struct sockaddr *)m_localInfo, &len);
        if(err == -1)
        {
        	throw( Exception( GetError() ) );
        }
    }

    int DataSocket::Send( const char *p_buffer, int p_size )
    {
    	if(m_connected == false)
    	{
    		throw( Exception(ENotConnected) );
    	}

    	int err = send(m_sock, p_buffer, p_size, 0);
    	if(err == -1)
    	{
    		// 非阻塞模式下，阻塞错误相当于发送0字节，不抛出异常而交给上层处理。
    		Error errno = GetError();
    		if(errno != EOperationWouldBlock)
    		{
    			throw( Exception(errno) );
    		}
    		err = 0;
    	}

    	return err;
    }

    int DataSocket::Receive( char *p_buffer, int p_size )
    {
    	if(m_connected == false)
    	{
    		throw( Exception(ENotConnected) );
    	}

    	int err = recv( m_sock, p_buffer, p_size, 0 );
    	if( err == 0 )
    	{
    		throw Exception( EConnectionClosed );
    	}
    	if( err == -1 )
    	{
    		throw Exception( GetError() );
    	}

    	return err;
    }

    void DataSocket::Close()
    {
    	if( m_connected == true )
    	{
    		shutdown( m_sock, 2 );
    	}
    	Socket::Close();

    	m_connected = false;
    }


    // ------------------------------------------------------------


}	// end namespace Network
}	// end namespace Fengine

