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

#ifndef __FENGINE_THREAD_UTILS_H__
#define __FENGINE_THREAD_UTILS_H__


#ifdef _WIN32
	#include <Windows.h>
	#include <map>
#else
	#include <pthread.h>
	#include <unistd.h>
#endif


namespace Fengine
{
namespace Thread
{
	typedef void (*ThreadFunc)(void *);

	#ifdef _WIN32
		typedef DWORD ThreadID;
		extern std::map<ThreadID, HANDLE> g_handleMap;
	#else
		typedef pthread_t ThreadID;
	#endif

	struct DummyData
	{
		ThreadFunc m_func;
		void *m_data;
	};

	#ifdef _WIN32
		DWORD WINAPI DummyRun(void *p_data);
	#else
		void *DummyRun(void *p_data);
	#endif

	ThreadID Create(ThreadFunc p_func, void *p_data);

	inline ThreadID GetID()
	{
#ifdef _WIN32
		return GetCurrentThreadId();
#else
		return pthread_self();
#endif
	}

	void WaitForFinish(ThreadID p_threadID);

	inline void Kill(ThreadID p_threadID)
	{
	#ifdef _WIN32
		TerminateThread(g_handleMap[p_threadID], 0);
		CloseHandle(g_handleMap[p_threadID]);
		g_handleMap.erase(p_threadID);
	#else
		pthread_cancel(p_threadID);
	#endif
	}

	inline void YieldThread(int p_milliseconds = 0)
	{
	#ifdef _WIN32
		Sleep(p_milliseconds);			// 毫秒级
	#else
		usleep(p_milliseconds * 1000);	// 微秒级
	#endif
	}

}	// end namespace Thread

}	// end namespace Fengine


#endif	// __FENGINE_THREAD_UTILS_H__