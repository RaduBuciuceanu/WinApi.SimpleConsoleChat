#pragma once

#include "Wascc.Networking.Io/IConnectionFactory.h"
#include "Wascc.Networking.Io/Preprocessor.h"

#include <winsock2.h>

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO ClientConnectionFactory : public IConnectionFactory
	{
	private:
		const char* _ipAddress;
		const char* _port;
		addrinfo* _addressInfo;
		SOCKET _socket;

	public:
		explicit ClientConnectionFactory(const char* ipAddress, const char* port);
		~ClientConnectionFactory() override;
		const IConnection* make() const override;

	private:
		SOCKET buildSocket() const;
	};
}
