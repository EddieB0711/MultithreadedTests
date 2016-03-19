#include "multi_thread_test_utils.h"

#include "test_thread_factory.h"
#include "i_test_threads.h"

auto create_tests() -> std::vector<p_test_threads>
{
	auto thread_factory = std::make_shared<test_thread_factory>();

	return std::vector<p_test_threads>
	{
		//thread_factory->create_thread_test(test_thread_type::pool_thread),
		//thread_factory->create_thread_test(test_thread_type::thread_class),
		thread_factory->create_thread_test(test_thread_type::compare_with_contention)
	};
}

auto main() -> int
{
	auto const & tests = create_tests();
	for (auto const & test : tests) test->run_test();

	getchar();

	return 0;
}