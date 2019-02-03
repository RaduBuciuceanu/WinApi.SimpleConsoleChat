#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#include <Wascc.Console.Io/Console.h>
#include <Wascc.Networking.Io/ClientConnectionFactory.h>
#include <exception>

using namespace Wascc::Networking::Io;
using std::exception;

const IConnectionFactory* factory;
const IConnection* connection;

const IConnectionFactory* buildConnectionFactory();
const IConnection* buildConnection();

int main()
{
	Console::writeLine("Client started...");

	try
	{
		factory = buildConnectionFactory();
		connection = buildConnection();
		connection->sendBytes("123");
	}
	catch (const exception& e)
	{
		Console::writeLine(e.what());
	}

	delete connection;
	delete factory;

	Console::write("Client stopped...");
	return Console::readKey();
}

const IConnectionFactory* buildConnectionFactory()
{
	Console::writeLine("Initializing client connection factory...");
	const IConnectionFactory* factory = new ClientConnectionFactory("127.0.0.1", "9090");
	Console::writeLine("Client connection factory was initialized...");
	return factory;
}

const IConnection* buildConnection()
{
	Console::writeLine("Opening a connction with server...");
	const IConnection* connection = factory->make();
	Console::writeLine("Connction with server was opened...");
	return connection;
}
