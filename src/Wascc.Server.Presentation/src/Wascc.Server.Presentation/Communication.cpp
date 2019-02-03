#include "Wascc.Server.Presentation/Communication.h"

namespace Wascc::Server::Presentation
{
	Communication::Communication(const IConnection* connection,
	                             const CommunicationRepository* communicationRepository)
	{
		_connection = const_cast<IConnection*>(connection);
		_communicationRepository = const_cast<CommunicationRepository*>(communicationRepository);
	}

	Communication::~Communication()
	{
		delete _connection;
	}

	void Communication::start()
	{
		thread communicationThread(&Communication::execute, this);
		communicationThread.detach();
	}

	string Communication::getName() const
	{
		return _name;
	}

	const IConnection* Communication::getConnection() const
	{
		return _connection;
	}

	void Communication::receiveName()
	{
		_name = _connection->receiveBytes(256);
		Console::writeLine("[" + _name + "]: " + "Connection was accepted.");
	}

	void Communication::sendOthers(const char* const message) const
	{
		string authorizedMessage = "[" + _name + "]: " + message;

		for (auto communication : _communicationRepository->getAll())
		{
			if (communication->getName() != _name)
			{
				communication->getConnection()->sendBytes(authorizedMessage.c_str());
			}
		}
	}

	void Communication::execute()
	{
		receiveName();

		while (executeOnce())
		{
		}
	}

	bool Communication::executeOnce() const
	{
		try
		{
			const auto receivedBytes = _connection->receiveBytes(256);
			Console::writeLine("[" + _name + "]: " + receivedBytes);
			sendOthers(receivedBytes);
		}
		catch (const std::exception&)
		{
			Console::writeLine("[" + _name + "]: " + "Connection was released.");
			return false;
		}

		return true;
	}
}
