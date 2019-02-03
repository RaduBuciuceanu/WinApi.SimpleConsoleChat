#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#include <Wascc.Console.Io/Console.h>
#include <Wascc.Networking.Io/ClientConnectionFactory.h>
#include <exception>
#include <thread>

using namespace Wascc::Networking::Io;
using std::exception;
using std::thread;

const IConnectionFactory* factory;
const IConnection* connection;
string name;

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
	Console::writeLine("Connection with server was opened...");
	return connection;
}

void sendMessages()
{
	while (true)
	{
		string message = Console::readLine();
		connection->sendBytes(message.c_str());
	}
}

void receiveMessages()
{
	while (true)
	{
		const auto message = connection->receiveBytes(256);
		Console::writeLine(message);
	}
}

int main()
{
	Console::writeLine("Client started...");
	Console::write("Name: ");
	name = Console::readLine();

	try
	{
		factory = buildConnectionFactory();
		connection = buildConnection();
		connection->sendBytes(name.c_str());

		thread(sendMessages).detach();
		receiveMessages();
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
