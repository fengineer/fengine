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

#include "Connection.h"

namespace Fengine
{
namespace Network
{
	template<typename PROTOCOL, typename Command>
	class ConnectionHandler
	{
		typedef Connection<PROTOCOL, Command> CONNECTION;
	public:
		ConnectionHandler(CONNECTION &p_conn)
			:m_connection(&p_conn)
		{
		}

		virtual void Enter() = 0;

		virtual void Leave() = 0;

		virtual void Handle(Command p_data) = 0;

		virtual void Hangup() = 0;

		virtual void Flooded() = 0;

		// 每个Handler都必须定义一个符合自身的静态函数NoRoom，以便处理未有Handler实例时的错误处理
		// static void NoRoom(CONNECTION &p_conn);
	protected:
		CONNECTION *m_connection;
	};

}	// end namespace Network

}	// end namespace Fengine