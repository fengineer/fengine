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

#ifndef __TIME_H__
#define __TIME_H__

#include "BasicTypes.h"

namespace Fengine
{

sint64 GetTimeMS();	// millisecond
sint64 GetTimeS();	// second
sint64 GetTimeM();	// minute
sint64 GetTimeH();	// hour

}	// end namespace Fengine


#endif // __TIME_H__