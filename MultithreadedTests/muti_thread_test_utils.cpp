#include "multi_thread_test_utils.h"

auto get_optimal_threads() noexcept -> DWORD
{
	auto info = SYSTEM_INFO { };

	GetSystemInfo(&info);

	return info.dwNumberOfProcessors;
}

auto test_iterations() -> std::vector<int>
{
	return std::vector<int> { 25, 50, 75, 100 }; // amount of work each iteration should do.
}