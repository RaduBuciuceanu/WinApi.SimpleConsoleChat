#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <Wascc.Console.Io/Console.h>
#include <Wascc.Networking.Io/ServerConnectionFactory.h>
#include <Wascc.Networking.Io/TcpConnection.h>

using namespace Wascc::Networking::Io;

IConnectionFactory* factory;
const IConnection* connection;

void execute();

int main()
{
	try
	{
		execute();
	}
	catch (const std::exception& e)
	{
		Console::writeLine(e.what());
	}

	delete factory;
	delete connection;

	return Console::readKey();
}

void execute()
{
	factory = new ServerConnectionFactory("9090");
	Console::writeLine("Factory was initialized.");

	Console::writeLine("Starting to accept a connection.");
	connection = factory->make();
	Console::writeLine("Connection was accepted.");

	Console::writeLine("Waiting for a message.");
	const auto receivedMessage = connection->receiveBytes(3);
	Console::write("Message received.");
	Console::writeLine(receivedMessage);
}
