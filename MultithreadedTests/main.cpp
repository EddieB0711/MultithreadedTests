#include "multi_thread_test_utils.h"
#include "p_test_threads.h"

#include "pool_thread_tests.h"
#include "log_pool_thread_results.h"

#include "thread_class_tests.h"

auto main() -> int
{
	auto tests = std::vector<p_test_threads>
	{
		make<pool_thread_tests>(make<log_pool_thread_results>("thread-pool-results.txt")),
		make<thread_class_tests>(make<log_pool_thread_results>("thread-class-results.txt"))
	};

	for (auto const & test : tests) test->run_test();

	getchar();

	return 0;
}