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

#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__

namespace Fengine
{

#ifdef __GNUC__
	typedef long long int sint64;
	typedef unsigned long long int uint64;
#endif

#ifdef _WIN32
	typedef __int64 sint64;
	typedef unsigned __int64 uint64;
#endif

typedef signed long int int32;
typedef unsigned long int uint32;
typedef signed short int int16;
typedef unsigned short int uint16;
typedef signed char int8;
typedef unsigned char uint8;

}	// end namespace Fengine

#endif // __BASIC_TYPES_H__