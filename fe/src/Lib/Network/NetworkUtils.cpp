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

#include "NetworkUtils.h"

#include "NetworkErrors.h"

namespace Fengine
{
namespace Network
{

    #ifdef _WIN32
    class System
    {
    public:
        System()
        {
            WSAStartup(MAKEWORD(2, 2), &m_wsaData);
        }

        ~System()
        {
            WSACleanup();
        }

    protected:
        WSADATA m_wsaData;
    };

    System g_system;
    #endif


    bool IsIPAddress(const std::string p_address)
    {
        for (size_t i = 0; i < p_address.size(); ++i)
        {
            if ((p_address[i] < '0' || p_address[i] > '9') && p_address[i] != '.')
            {
                return false;
            }
        }

        return true;
    }

    IP_ADDRESS GetIPAddress(const std::string p_strAddress)
    {
        if (IsIPAddress(p_strAddress))
        {
            IP_ADDRESS ipAddress = inet_addr(p_strAddress.c_str());
            if (ipAddress == INADDR_NONE)
            {
                throw Exception(GetError());
            }

            return ipAddress;
        }
        else
        {
            struct hostent *host = gethostbyname(p_strAddress.c_str());
            if (host == NULL)
            {
                throw Exception(GetError(false));
            }

            return *((IP_ADDRESS *)host->h_addr);
        }
    }

    std::string GetIPString(IP_ADDRESS p_address)
    {
        char *addrstr = inet_ntoa(*((in_addr*)&p_address));
        if (addrstr == NULL)
        {
            return std::string("Invalid IP Address");
        }

        return std::string(addrstr);
    }

    std::string GetHostNameString(IP_ADDRESS p_address)
    {
        struct hostent* host = gethostbyaddr((char*)&p_address, 4, AF_INET);

        if (host == NULL)
        {
            // get the error from h_errno.
            throw Exception(GetError(false));
        }

        return std::string(host->h_name);
    }

}   // end namespace Network

}   // end namespace Fengine