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

#ifndef __FENGINE_THREAD_EXCEPTION_H__
#define __FENGINE_THREAD_EXCEPTION_H__

#include <exception>

namespace Fengine
{
namespace Thread
{
	enum Error
	{
		Unspecified,	// 未定义错误
		InitFailure,	// 线程库初始化错误
		CreationFailure	// 线程无法被创建
	};


	class Exception: std::exception
	{
	public:
		Exception(Error p_error = Unspecified)
			:m_error(p_error)
		{
		}

		Error GetError()
		{
			return m_error;
		}

	protected:

		Error m_error;
	};


}	// end namespace Thread
}	// end namespace Fengine


#endif	// __FENGINE_THREAD_EXCEPTION_H__

