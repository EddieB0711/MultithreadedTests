#pragma once

#include "unique_handle.h"
#include "environment_handle.h"
#include "event_handle.h"
#include "multi_thread_test_utils.h"

namespace multi_threading
{
	class thread_environment
	{
		environment_handle m_environment;
		pool_handle m_pool;
		cleanupgroup_handle m_cleanupgroup;

	public:
		thread_environment(thread_environment const &) = delete;
		thread_environment(thread_environment &&) = delete;
		auto operator =(thread_environment const &) -> thread_environment & = delete;
		auto operator =(thread_environment &&) -> thread_environment & = delete;

		thread_environment(DWORD maxThreads = get_optimal_threads());

		template <typename W>
		auto submit(W work, void * args = nullptr) noexcept -> void
		{
			auto w = CreateThreadpoolWork(work, args, m_environment.get());

			SubmitThreadpoolWork(w);
		}

		auto wait() noexcept -> void;
	};
}