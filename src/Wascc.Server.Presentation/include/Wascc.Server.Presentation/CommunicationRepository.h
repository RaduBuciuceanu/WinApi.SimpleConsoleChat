#pragma once

#include <vector>
#include <mutex>

namespace Wascc::Server::Presentation
{
	using std::vector;
	using std::mutex;

	class Communication;

	class CommunicationRepository
	{
	private:
		vector<const Communication*> _communications;
		static mutex _mutex;

	public:
		~CommunicationRepository();
		void insert(const Communication* communication);
		vector<const Communication*> getAll() const;
	};
}
