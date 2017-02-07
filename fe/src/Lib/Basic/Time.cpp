
#include "Time.h"

#include <time.h>

#ifdef _WIN32
    #include "windows.h"
#else
    #include <sys/time.h>
#endif


namespace Fengine
{
    #ifdef _WIN32
        class Win32PerformanceFrequency
        {
        public:
            Win32PerformanceFrequency()
            {
                QueryPerformanceFrequency((LARGE_INTEGER *)&m_frequency);   // 获取机器固有的性能频率
                m_frequency /= 1000;    // 每毫秒多少次
            }

            sint64 GetFrequency()
            {
                return m_frequency;
            }
        private:
            sint64 m_frequency;
        };

        Win32PerformanceFrequency g_win32Frequency;
    #endif

    sint64 GetTimeMS()
    {
    #ifdef _WIN32
        sint64 tick;
        QueryPerformanceCounter((LARGE_INTEGER *)&tick);    // 系统启动至今的性能计数
        return tick / g_win32Frequency.GetFrequency();
    #else
        struct timeval t;
        sint64 ms;
        
        gettimeofday(&t, 0);
        ms = t.tv_sec;              // t.tv_sec为int32，复制到sint64后再做乘法运算避免溢出
        ms *= 1000;                 // 秒转为毫秒
        ms += (t.tv_usec / 1000);   // 微秒转为毫秒

        return ms;
    #endif
    }

    sint64 GetTimeS()
    {
        return GetTimeMS() / 1000;
    }

    sint64 GetTimeM()
    {
        return GetTimeMS() / 60000;
    }

    sint64 GetTimeH()
    {
        return GetTimeMS() / 3600000;
    }


}	// end namespace Fingine.



