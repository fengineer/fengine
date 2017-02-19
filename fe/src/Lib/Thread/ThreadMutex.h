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

#ifndef __FENGINE_THREAD_MUTEX_H__
#define __FENGINE_THREAD_MUTEX_H__

#ifdef _WIN32
	#include <Windows.h>
#else
	#include <pthread.h>
#endif


namespace Fengine
{
namespace Thread
{

	class Mutex
	{
	public:
		Mutex()
		{
		#ifdef _WIN32
			// 使用critical sections会快很多，不需要用使用win平台的重量级互斥锁
			InitializeCriticalSection( &m_mutex );
		#else
			pthread_mutex_init( &m_mutex, 0 );
		#endif
		}

		~Mutex()
		{
		#ifdef _WIN32
			DeleteCriticalSection(&m_mutex);
		#else
			pthread_mutex_destroy(&m_mutex);
		#endif
		}

		void Lock()
		{
		#ifdef _WIN32
			EnterCriticalSection(&m_mutex);
		#else
			pthread_mutex_lock(&m_mutex);
		#endif
		}

		void UnLock()
		{
		#ifdef _WIN32
			LeaveCriticalSection(&m_mutex);
		#else
			pthread_mutex_unlock( &m_mutex );
		#endif
		}

	protected:
		#ifdef _WIN32
			CRITICAL_SECTION m_mutex;
		#else
			pthread_mutex_t m_mutex;
		#endif

	};

}	// end namespace Thread

}	// end namespace Fengine

#endif // __FENGINE_THREAD_MUTEX_H__