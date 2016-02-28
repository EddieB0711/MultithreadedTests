#pragma once

#include "multi_threaded_work.h"
#include "p_log_results.h"

#include <vector>
#include <Windows.h>

auto get_optimal_threads() noexcept -> DWORD;

namespace multi_threading
{
	class thread_environment;
}

auto create_bounded_iterations(int work) -> bounded_iterations;

template <typename T, typename... Args>
std::shared_ptr<T> make(Args &&... args)
{
	return std::make_shared<T>(args...);
}

auto test_iterations() -> std::vector<int>;