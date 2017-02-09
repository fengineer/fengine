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
		Socket::Socket()
			:m_sock(0),
			m_isBlocking(false)
		{
		}

		void SetBlocking(bool p_isBlocking)
		{
			int err;
			#ifdef _WIN32
				// todo
			#else
			#endif
		}
	}	// end namespace Network


}	// end namespace Network