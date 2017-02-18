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

#ifndef __NETWORK_TYPES_H__
#define __NETWORK_TYPES_H__

#ifdef _WIN32
	#include "winsock2.h"
	#include "Ws2tcpip.h"

	#ifndef socklen_t
		typedef int socklen_t;
	#endif
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <fcntl.h>
#endif


namespace Fengine
{

namespace Network
{
#ifdef _WIN32
    typedef SOCKET SOCK;
#else
    typedef int SOCK;
#endif

    typedef unsigned short int PORT;
    typedef unsigned long int IP_ADDRESS;

}	// end namespace Network

}	// end namespace Fengine



#endif	// __NETWORK_TYPES_H__