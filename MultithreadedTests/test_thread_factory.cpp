#include "test_thread_factory.h"

#include "log_pool_thread_results.h"
#include "log_thread_contention_results.h"

#include "thread_class_tests.h"
#include "pool_thread_tests.h"
#include "thread_comparison_with_contention.h"

namespace test_factory
{
	auto create_thread_class_test() noexcept -> p_test_threads
	{
		return std::make_shared<thread_class_tests>(std::make_shared<log_pool_thread_results>("thread-class-results.txt", "Number Of Iterations, Thread Class Time"));
	}

	auto create_pool_thread_test() noexcept -> p_test_threads
	{
		return std::make_shared<pool_thread_tests>(std::make_shared<log_pool_thread_results>("thread-pool-results.txt", "Number Of Iterations, Threadpool Time"));
	}

	auto create_thread_comparison_with_contention(std::shared_ptr<i_test_thread_factory> const & thread_factory) noexcept -> p_test_threads
	{
		return std::make_shared<thread_comparison_with_contention>(std::make_shared<log_thread_contention_results>("thread_comparison_with_contention.txt"), thread_factory);
	}
}

auto test_thread_factory::create_thread_test(test_thread_type test_type) noexcept -> p_test_threads
{
	switch (test_type)
	{
	case test_thread_type::thread_class: return test_factory::create_thread_class_test();
	case test_thread_type::pool_thread: return test_factory::create_pool_thread_test();
	case test_thread_type::compare_with_contention: return test_factory::create_thread_comparison_with_contention(shared_from_this());
	default: return nullptr;
	}
}