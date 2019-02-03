#include "Wascc.Networking.Io/ClientConnectionFactory.h"

#include "ConnectionFactoryHelper.h"
#include "Wascc.Networking.Io/TcpConnection.h"

#include <Windows.h>
#include <exception>
#include <ws2tcpip.h>

namespace Wascc::Networking::Io
{
	using std::exception;

	ClientConnectionFactory::ClientConnectionFactory(const char* ipAddress, const char* port)
	{
		_ipAddress = ipAddress;
		_port = port;

		ConnectionFactoryHelper::initializeWsa();
		_addressInfo = ConnectionFactoryHelper::buildAddressInfo(ipAddress, port);
		_socket = buildSocket();
	}

	ClientConnectionFactory::~ClientConnectionFactory()
	{
		freeaddrinfo(_addressInfo);
		shutdown(_socket, SD_SEND);
		closesocket(_socket);
		WSACleanup();
	}

	const IConnection* ClientConnectionFactory::make() const
	{
		return new TcpConnection(_socket);
	}

	SOCKET ClientConnectionFactory::buildSocket() const
	{
		SOCKET result = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
		ConnectionFactoryHelper::handleInvalidSocket(result, "Unable to connect to server.");
		connect(result, _addressInfo->ai_addr, _addressInfo->ai_addrlen);
		return result;
	}
}