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

#include "Telnet.h"

namespace Fengine
{
namespace Network
{

	void Telnet::Translate(Connection<Telnet> &p_conn, char* p_buffer, int p_size)
	{
		for (int i = 0; i < p_size; i++)
		{
			char c = p_buffer[i];
			// 如果是字母，缓冲区也没满，加入到缓冲区
			if ( c >= 32 && c != 127 && m_buffersize < BUFFERSIZE )
			{ 
				m_buffer[m_buffersize] = c;
				m_buffersize++;
			}
			// 如果是退格符，删除最后一个字符
			else if (c == 8 && m_buffersize > 0)
			{
				m_buffersize--;
			}
			// 如果是回车换行，命令结束，可以处理了
			else if (c == '\r' || c == '\n')
			{
				// 如果符合条件，把缓冲区封装成字符串发送给连接的处理器
				if (m_buffersize > 0 && p_conn.Handler() != NULL)
				{
					p_conn.Handler()->Handle(std::string(m_buffer, m_bufferSize));
				}

				m_bufferSize = 0;
			}
		}
	}

	void SendString( Connection<Telnet> &p_conn, std::string p_string )
	{
		p_conn.BufferData(p_string.data(), (int)p_string.size());
	}


}	// end namespace Network

}	// end namespace Fengine