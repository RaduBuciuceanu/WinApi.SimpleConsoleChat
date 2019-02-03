#pragma once

#include "Wascc.Networking.Io/IConnection.h"
#include "Wascc.Networking.Io/Preprocessor.h"

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO IConnectionFactory
	{
	public:
		virtual ~IConnectionFactory()
		{
		}

		virtual const IConnection* make() const = 0;
	};
}
