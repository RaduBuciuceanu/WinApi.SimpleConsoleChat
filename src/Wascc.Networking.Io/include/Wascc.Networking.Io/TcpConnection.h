#pragma once

#include "Wascc.Networking.Io/IConnection.h"
#include "Wascc.Networking.Io/Preprocessor.h"

#include <winsock2.h>

namespace Wascc::Networking::Io
{
	class WASCC_NETWORKING_IO TcpConnection : public IConnection
	{
	private:
		SOCKET _socket;

	public:
		explicit TcpConnection(const SOCKET socket);
		~TcpConnection() override;

		const char* sendBytes(const char* value) const override;
		const char* receiveBytes(const int bufferLength) const override;
	};
}
