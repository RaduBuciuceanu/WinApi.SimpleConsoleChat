#pragma once

#include "Wascc.Networking.Io/IConnectionFactory.h"
#include "Wascc.Networking.Io/Preprocessor.h"
#include <winsock2.h>

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO ConnectionFactoryHelper
	{
	private:
		addrinfo* _addressInfo;
		SOCKET _socket;

	public:
		static void handleErrorCode(int errorCode, const char* message);
		static void handleInvalidSocket(SOCKET socket, const char* message);
		static void initializeWsa();
		static addrinfo* buildAddressInfo(const char* ipAddress, const char* port);

	private:
		static addrinfo buildHintAddressInfo();
	};
}
