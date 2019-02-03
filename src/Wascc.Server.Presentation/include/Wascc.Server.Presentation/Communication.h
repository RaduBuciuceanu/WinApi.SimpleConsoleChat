#pragma once

#include "Wascc.Server.Presentation/Preprocessor.h"
#include "Wascc.Server.Presentation/CommunicationRepository.h"

#include <Wascc.Console.Io/Console.h>
#include <Wascc.Networking.Io/IConnection.h>
#include <thread>


namespace Wascc::Server::Presentation
{
	using Networking::Io::IConnection;
	using std::thread;

	class WASCC_SERVER_PRESENTATION Communication
	{
	private:
		string _name;
		IConnection* _connection;
		CommunicationRepository* _communicationRepository;

	public:
		Communication(const IConnection* connection, const CommunicationRepository* communicationRepository);
		~Communication();
		void start();
		string getName() const;
		const IConnection* getConnection() const;

	private:
		void execute();
		void receiveName();
		void sendOthers(const char* const message) const;
		bool executeOnce() const;
	};
}
