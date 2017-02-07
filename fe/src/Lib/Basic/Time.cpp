
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
                QueryPerformanceFrequency((LARGE_INTEGER *)&m_frequency);   // ��ȡ�������е�����Ƶ��
                m_frequency /= 1000;    // ÿ������ٴ�
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
        QueryPerformanceCounter((LARGE_INTEGER *)&tick);    // ϵͳ������������ܼ���
        return tick / g_win32Frequency.GetFrequency();
    #else
        struct timeval t;
        sint64 ms;
        
        gettimeofday(&t, 0);
        ms = t.tv_sec;              // t.tv_secΪint32�����Ƶ�sint64�������˷�����������
        ms *= 1000;                 // ��תΪ����
        ms += (t.tv_usec / 1000);   // ΢��תΪ����

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



