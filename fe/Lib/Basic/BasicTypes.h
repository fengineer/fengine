
#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__

namespace Fengine
{

#ifdef __GNUC__
	typedef long long int sint64;
	typedef unsigned long long int uint64;
#endif

#ifdef WIN32
	typedef __int64 sint64;
	typedef unsigned __int64 uint64;
#endif

typedef signed long int int32;
typedef unsigned long int uint32;
typedef signed short int int16;
typedef unsigned short int uint16;
typedef signed char int8;
typedef unsigned char uint8;

}	// end of namespace Fengine

#endif // end of __BASIC_TYPES_H__