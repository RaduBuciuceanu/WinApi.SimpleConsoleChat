#include "Wascc.Networking.Io/TcpConnection.h"

#include <string.h>

namespace Wascc::Networking::Io
{
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
		auto buffer = new char[bufferLength];
		recv(_socket, buffer, bufferLength, 0);
		return buffer;
	}
}
