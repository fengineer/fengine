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

#include "NetworkTypes.h"

#include <string>

namespace Fengine
{

namespace Network
{
    // 检查一个字符串是否是ip地址格式
    bool IsIPAddress(const std::string p_address);

    // convert ip like as "172.16.0.173" to IP_ADDRESS，触发DNS查询会导致阻塞。
    IP_ADDRESS GetIPAddress(const std::string p_strAddress);

    // convert IP_ADDRESS to type like as "172.16.0.173"
    std::string GetIPString(IP_ADDRESS p_address);

    // 使用DNS查询转换一个IP_ADDRESS地址为字符串模式，会导致阻塞
    std::string GetHostNameString(IP_ADDRESS p_address);

}   // end namespace Network

}   // end namespace Fengine