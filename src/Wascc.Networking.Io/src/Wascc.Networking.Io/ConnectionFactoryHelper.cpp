#include "ConnectionFactoryHelper.h"

#include <exception>
#include <ws2tcpip.h>

namespace Wascc::Networking::Io
{
	using std::exception;

	void ConnectionFactoryHelper::handleErrorCode(const int errorCode, const char* message)
	{
		if (errorCode)
		{
			throw exception(message);
		}
	}

	void ConnectionFactoryHelper::handleInvalidSocket(const SOCKET socket, const char* message)
	{
		if (socket == INVALID_SOCKET || socket == SOCKET_ERROR)
		{
			throw exception(message);
		}
	}

	void ConnectionFactoryHelper::initializeWsa()
	{
		WSADATA wsaData;
		const int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
		handleErrorCode(errorCode, "Failed to execute the WSA startup.");
	}

	addrinfo* ConnectionFactoryHelper::buildAddressInfo(const char* ipAddress, const char* port)
	{
		addrinfo* result;
		addrinfo hints = buildHintAddressInfo();
		const int errorCode = getaddrinfo(ipAddress, port, &hints, &result);
		handleErrorCode(errorCode, "Failed to generate the address info.");
		return result;
	}

	addrinfo ConnectionFactoryHelper::buildHintAddressInfo()
	{
		struct addrinfo hints;
		ZeroMemory(&hints, sizeof hints);
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;
		return hints;
	}
}