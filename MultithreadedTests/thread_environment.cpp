#include "thread_environment.h"

namespace multi_threading
{
	thread_environment::thread_environment(DWORD maxThreads) :
		m_pool { CreateThreadpool(nullptr) },
		m_cleanupgroup { CreateThreadpoolCleanupGroup() }
	{
		SetThreadpoolThreadMaximum(m_pool.get(), maxThreads);

		if (!SetThreadpoolThreadMinimum(m_pool.get(), 1))
		{
			throw windows_exception();
		}

		SetThreadpoolCallbackPool(m_environment.get(), m_pool.get());

		SetThreadpoolCallbackCleanupGroup(m_environment.get(),
										  m_cleanupgroup.get(),
										  nullptr);
	}

	auto thread_environment::wait() noexcept -> void
	{
		CloseThreadpoolCleanupGroupMembers(m_cleanupgroup.get(),
										   false,
										   nullptr);
	}
}