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

#ifndef __TELNET_H__
#define __TELNET_H__

#include <string>
#include "Connection.h"
#include "ConnectionHandler.h"
#include "Protocol.h"

namespace Fengine
{
namespace Network
{
	// vt100控制码定义
	const std::string reset = "\x1B[0m";
	const std::string bold = "\x1B[1m";
	const std::string dim = "\x1B[2m";
	const std::string under = "\x1B[4m";
	const std::string reverse = "\x1B[7m";
	const std::string hide = "\x1B[8m";

	const std::string clearscreen = "\x1B[2J";
	const std::string clearline = "\x1B[2K";

	const std::string black = "\x1B[30m";
	const std::string red = "\x1B[31m";
	const std::string green = "\x1B[32m";
	const std::string yellow = "\x1B[33m";
	const std::string blue = "\x1B[34m";
	const std::string magenta = "\x1B[35m";
	const std::string cyan = "\x1B[36m";
	const std::string white = "\x1B[37m";

	const std::string bblack = "\x1B[40m";
	const std::string bred = "\x1B[41m";
	const std::string bgreen = "\x1B[42m";
	const std::string byellow = "\x1B[43m";
	const std::string bblue = "\x1B[44m";
	const std::string bmagenta = "\x1B[45m";
	const std::string bcyan = "\x1B[46m";
	const std::string bwhite = "\x1B[47m";

	const std::string newline = "\r\n\x1B[0m";

	class Telnet : public Protocol<Telnet, std::string>
	{
	public:
		Telnet()
			:m_bufferSize(0)
		{
		}

		void Translate( Connection<Telnet> &p_conn, char* p_buffer, int p_size );

		void SendString( Connection<Telnet> &p_conn, std::string p_string );

		int BufferedSize() { return m_bufferSize; }

	protected:
		char m_buffer[RECEIVE_BUFFER_SIZE];
		int m_bufferSize;

	};

}	// end namespace Network

}	// end namespace Fengine

#endif	// __TELNET_H__