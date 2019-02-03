#include "Wascc.Networking.Io/ServerConnectionFactory.h"

#include <exception>
#include <ws2tcpip.h>

#include "ConnectionFactoryHelper.h"
#include "Wascc.Networking.Io/TcpConnection.h"

namespace Wascc::Networking::Io
{
	using std::exception;

	ServerConnectionFactory::ServerConnectionFactory(const char* port)
	{
		ConnectionFactoryHelper::initializeWsa();
		_addressInfo = ConnectionFactoryHelper::buildAddressInfo(nullptr, port);
		_socket = buildSocket();
	}

	ServerConnectionFactory::~ServerConnectionFactory()
	{
		freeaddrinfo(_addressInfo);
		closesocket(_socket);
		WSACleanup();
	}

	const IConnection* ServerConnectionFactory::make() const
	{
		const SOCKET accepted = accept(_socket, nullptr, nullptr);
		ConnectionFactoryHelper::handleInvalidSocket(accepted, "Failed to accept a client socket.");
		return new TcpConnection(accepted);
	}

	SOCKET ServerConnectionFactory::buildSocket() const
	{
		const SOCKET result = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
		ConnectionFactoryHelper::handleInvalidSocket(result, "Failed to create the listener socket.");
		const int bindErrorCode = bind(result, _addressInfo->ai_addr, _addressInfo->ai_addrlen);
		ConnectionFactoryHelper::handleErrorCode(bindErrorCode, "Failed to bind the listener socket.");
		const int listenErrorCode = listen(result, SOMAXCONN);
		ConnectionFactoryHelper::handleErrorCode(listenErrorCode, "Failed to listen the listener socket.");

		return result;
	}
}
