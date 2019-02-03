#pragma once

#include "Wascc.Networking.Io/Preprocessor.h"

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO IConnection
	{
	public:
		virtual ~IConnection()
		{
		}

		virtual const char* sendBytes(const char* value) const = 0;
		virtual const char* receiveBytes(const int bufferLength) const = 0;
	};
}
