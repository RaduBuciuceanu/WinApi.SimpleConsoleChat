#pragma once

#include "Wascc.Networking.Io/IConnectionFactory.h"
#include "Wascc.Networking.Io/Preprocessor.h"
#include <winsock2.h>

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO ServerConnectionFactory : public IConnectionFactory
	{
	private:
		addrinfo* _addressInfo;
		SOCKET _socket;

	public:
		explicit ServerConnectionFactory(const char* port);
		~ServerConnectionFactory();
		const IConnection* make() const override;

	private:
		SOCKET buildSocket() const;
	};
}
