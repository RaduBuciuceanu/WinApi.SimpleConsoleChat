#include "Wascc.Networking.Io/TcpConnection.h"

#include <string.h>
#include <exception>
#include <minwinbase.h>

namespace Wascc::Networking::Io
{
	using std::exception;

	TcpConnection::TcpConnection(const SOCKET socket)
	{
		_socket = socket;
	}

	TcpConnection::~TcpConnection()
	{
		closesocket(_socket);
	}

	const char* TcpConnection::sendBytes(const char* value) const
	{
		send(_socket, value, strlen(value), 0);
		return value;
	}

	const char* TcpConnection::receiveBytes(const int bufferLength) const
	{
		const auto buffer = new char[bufferLength];
		ZeroMemory(buffer, bufferLength);
		const int receivedCount = recv(_socket, buffer, bufferLength, 0);

		if (receivedCount <= 0)
		{
			throw exception("Connection closed.");
		}

		return buffer;
	}
}
