#pragma once

#include "multi_threaded_work.h"
#include "p_log_results.h"

auto get_optimal_threads() noexcept -> DWORD;

namespace multi_threading
{
	class thread_environment;
}

auto create_bounded_iterations(int work) -> bounded_iterations;

auto test_iterations() -> std::vector<int>;