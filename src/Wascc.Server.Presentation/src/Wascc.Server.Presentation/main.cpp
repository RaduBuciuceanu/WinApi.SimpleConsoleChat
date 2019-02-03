#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "Hypodermic/ContainerBuilder.h"
#include "Wascc.Server.Presentation/Communication.h"
#include "Wascc.Server.Presentation/CommunicationRepository.h"

#include <Wascc.Console.Io/Console.h>
#include <Wascc.Networking.Io/ServerConnectionFactory.h>
#include <Wascc.Networking.Io/TcpConnection.h>
#include <thread>
#include <vector>

using namespace Wascc::Networking::Io;
using namespace Wascc::Server::Presentation;

using std::string;
using std::thread;
using std::vector;

IConnectionFactory* factory;
CommunicationRepository* communicationRepository;

void initialize()
{
	communicationRepository = new CommunicationRepository();
	factory = new ServerConnectionFactory("9090");
	Console::writeLine("Listening for clients...");
}

void execute()
{
	while (true)
	{
		const IConnection* connection = factory->make();
		auto communication = new Communication(connection, communicationRepository);
		communicationRepository->insert(communication);
		communication->start();
	}
}

void listenForCommands()
{
	while (true)
	{
		Console::write(">");
		const string command = Console::readLine();

		if (command == "connections_count")
		{
			const int connectionsCount = communicationRepository->getAll().size();
			Console::writeLine("Connections count: " + std::to_string(connectionsCount));
		}
		else if (command == "show_connections")
		{
			for (auto communication : communicationRepository->getAll())
			{
				Console::writeLine(communication->getName());
			}
		}
		else if (command == "exit")
		{
			return;
		}
	}
}

int main()
{
	try
	{
		initialize();
		thread(execute).detach();
		listenForCommands();
	}
	catch (const std::exception& e)
	{
		Console::writeLine(e.what());
	}

	delete factory;
	delete communicationRepository;

	return Console::readKey();
}
