#pragma once

#include "Wascc.Networking.Io/IConnectionListener.h"
#include "Wascc.Networking.Io/Preprocessor.h"
#include <winsock2.h>

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO TcpConnectionListener : public IConnectionListener
	{
	private:
		addrinfo* _addressInfo;
		SOCKET _socket;

	public:
		explicit TcpConnectionListener(const char* port);
		~TcpConnectionListener();
		const IConnection* acceptOne() const override;

	private:
		static void handleErrorCode(int errorCode, const char* message);
		static void handleInvalidSocket(SOCKET socket, const char* message);
		static void initializeWsa();
		static addrinfo buildHintAddressInfo();
		static addrinfo* buildAddressInfo(const char* port);

		SOCKET buildSocket() const;
	};
}
