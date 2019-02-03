#include "Wascc.Server.Presentation/CommunicationRepository.h"

#include <Wascc.Server.Presentation/Communication.h>

namespace Wascc::Server::Presentation
{
	mutex CommunicationRepository::_mutex;

	CommunicationRepository::~CommunicationRepository()
	{
		_mutex.lock();

		for (auto communication : _communications)
		{
			delete communication;
		}

		_mutex.unlock();
	}

	void CommunicationRepository::insert(const Communication* communication)
	{
		_mutex.lock();
		_communications.push_back(communication);
		_mutex.unlock();
	}

	vector<const Communication*> CommunicationRepository::getAll() const
	{
		return _communications;
	}
}
