#include "Wascc.Networking.Io/TcpConnectionListener.h"

#include <exception>
#include <ws2tcpip.h>

#include "Wascc.Networking.Io/TcpConnection.h"

namespace Wascc::Networking::Io
{
	using std::exception;

	TcpConnectionListener::TcpConnectionListener(const char* port)
	{
		initializeWsa();
		_addressInfo = buildAddressInfo(port);
		_socket = buildSocket();
	}

	TcpConnectionListener::~TcpConnectionListener()
	{
		freeaddrinfo(_addressInfo);
		closesocket(_socket);
		WSACleanup();
	}

	const IConnection* TcpConnectionListener::acceptOne() const
	{
		const SOCKET accepted = accept(_socket, nullptr, nullptr);
		handleInvalidSocket(accepted, "Failed to accept a client socket.");
		return new TcpConnection(accepted);
	}

	void TcpConnectionListener::handleErrorCode(const int errorCode, const char* message)
	{
		if (errorCode)
		{
			throw exception(message);
		}
	}

	void TcpConnectionListener::handleInvalidSocket(const SOCKET socket, const char* message)
	{
		if (socket == INVALID_SOCKET)
		{
			throw exception(message);
		}
	}

	void TcpConnectionListener::initializeWsa()
	{
		WSADATA wsaData;
		const int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
		handleErrorCode(errorCode, "Failed to execute the WSA startup.");
	}

	addrinfo TcpConnectionListener::buildHintAddressInfo()
	{
		struct addrinfo hints;
		ZeroMemory(&hints, sizeof hints);
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;
		return hints;
	}

	addrinfo* TcpConnectionListener::buildAddressInfo(const char* port)
	{
		addrinfo* result;
		addrinfo hints = buildHintAddressInfo();
		const int errorCode = getaddrinfo(nullptr, port, &hints, &result);
		handleErrorCode(errorCode, "Failed to generate the address info.");
		return result;
	}

	SOCKET TcpConnectionListener::buildSocket() const
	{
		const SOCKET result = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
		handleInvalidSocket(result, "Failed to create the listener socket.");
		const int bindErrorCode = bind(result, _addressInfo->ai_addr, _addressInfo->ai_addrlen);
		handleErrorCode(bindErrorCode, "Failed to bind the listener socket.");
		const int listenErrorCode = listen(result, SOMAXCONN);
		handleErrorCode(listenErrorCode, "Failed to listen the listener socket.");

		return result;
	}
}
