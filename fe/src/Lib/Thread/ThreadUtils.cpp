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

#include "ThreadUtils.h"

#include "ThreadException.h"

namespace Fengine
{

namespace Thread
{
	#ifdef _WIN32
		std::map<ThreadID, HANDLE> g_handleMap;
	#endif

	#ifdef _WIN32
		DWORD WINAPI DummyRun(void *p_data)
	#else
		void *DummyRun(void *p_data)
	#endif
		{
			DummyData *dummy = ( DummyData * )p_data;
			dummy->m_func(dummy->m_data);

			delete dummy;

			return 0;
		}

	ThreadID Create(ThreadFunc p_func, void *p_data)
	{
		DummyData *data = new DummyData;
		data->m_func = p_func;
		data->m_data = p_data;

		ThreadID t;
		#ifdef _WIN32
			HANDLE h = CreateThread(NULL, 0, DummyRun, data, 0, &t );
			if(h != 0)
			{
				g_handleMap[t] = h;
			}
		#else
			pthread_create( &t, 0, DummyRun, data );
		#endif

		if( t == 0 )
		{
			delete data;
			throw Exception(CreationFailure);
		}

		return t;
	}

	void WaitForFinish(ThreadID p_threadID)
	{
#ifdef _WIN32
		WaitForSingleObject(g_handleMap[p_threadID], INFINITE);
		CloseHandle(g_handleMap[p_threadID]);
		g_handleMap.erase(p_threadID);
#else
		// join实质上是把控制权转交给p_threadID并等待它结束
		pthread_join(p_threadID, NULL);
#endif
	}
}	// end namespace Fengine

}	// end namespace Thread