#pragma once

#include "Wascc.Networking.Io/IConnection.h"
#include "Wascc.Networking.Io/Preprocessor.h"

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO IConnectionListener
	{
	public:
		virtual ~IConnectionListener()
		{
		}

		virtual const IConnection* acceptOne() const = 0;
	};
}
