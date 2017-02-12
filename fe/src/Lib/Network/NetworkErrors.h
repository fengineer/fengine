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

#ifndef __NETWORK_ERRORS_H__
#define __NETWORK_ERRORS_H__

#include <exception>
#include <string>

namespace Fengine
{

namespace Network
{
	enum Error
	{
		// errors that shouldn't happen, so if they do, something is wrong:
		ESeriousError,

		// these errors are common
		ENetworkDown,
		ENoSocketsAvailable,
		ENoMemory,
		EAddressNotAvailable,
		EAlreadyConnected,
		ENotConnected,
		EConnectionRefused,
		ENetworkUnreachable,
		ENetworkReset,
		EHostUnreachable,
		EHostDown,
		EConnectionAborted,
		EConnectionReset,
		EOperationWouldBlock,

		// DNS errors
		EDNSNotFound,
		EDNSError,
		ENoDNSData,

		// These errors are specific errors that should never or rarely occur.
		EInProgress,
		EInterrupted,
		EAccessDenied,
		EInvalidParameter,
		EAddressFamilyNotSupported,
		EProtocolFamilyNotSupported,
		EProtocolNotSupported,
		EProtocolNotSupportedBySocket,
		EOperationNotSupported,
		EInvalidSocketType,
		EInvalidSocket,
		EAddressRequired,
		EMessageTooLong,
		EBadProtocolOption,
		EAddressInUse,
		ETimedOut,
		EShutDown,

		// auxilliary socketlib errors
		ESocketLimitReached,
		ENotAvailable,
		EConnectionClosed
	}

	Error TranslateError(int p_error, bool p_fromErrno);

	Error GetError(bool p_fromErrno = true);

	class Exception : public std::exception
	{
	public:
		Exception(int p_code);

		Error ErrorCode();

		std::string ErrorString();

	protected:
		Error m_code;
	}

} // end namespace Network

} // end namespace Fengine

#endif	// __NETWORK_ERRORS_H__
