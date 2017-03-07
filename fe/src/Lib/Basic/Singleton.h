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

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <assert.h>
#include <stdio.h>

namespace Fengine
{

    template<typename T>
    class Singleton
    {
    public:
        T *InstancePtr()
        {
            if (m_instance == NULL)
            {
                Create();
            }
            return m_instance;
        }

        T &Instance()
        {
            if (m_instance == NULL)
            {
                Create();
            }
            return *m_instance;
        }

    protected:
        Singleton()
        {
            assert(m_instance == NULL);
            m_instance = static_cast<T *>(this);
        }

        void static Create()
        {
            if (m_instance == NULL)
            {
                m_instance = T();
            }
        }

    protected:
        static T *m_instance;

    };

    template<typename T>
    T *Singleton<T>::m_instance = NULL;

}   // end namespace Fengine


#endif // __SINGLETON_H__