#include "thread_comparison_with_contention.h"
#include "i_test_thread_factory.h"
#include "i_log_results.h"
#include "background_worker.h"

auto add_background_noise(bool const & terminate) -> void
{
	while (!terminate) for (auto a = 0; a < 1000; ++a) for (auto b = 0; b < 1000; ++b);
}

class terminate_guard
{
	bool & m_terminate;

public:
	explicit terminate_guard(bool & terminate) noexcept : m_terminate(terminate) {}
	~terminate_guard() noexcept { m_terminate = !m_terminate; }
};

auto run_comparison_test(p_log_results const & results_logger, p_test_thread_factory const & thread_factory, bool & terminate) -> void
{
	auto guard = terminate_guard { terminate };
	auto test_class_thread = thread_factory->create_thread_test(test_thread_type::thread_class);
	auto test_pool_thread = thread_factory->create_thread_test(test_thread_type::pool_thread);

	TRACE_LINE(L"Starting Thread Class Test");
	test_class_thread->run_test();

	TRACE_LINE(L"Starting Pool Thread Test");
	test_pool_thread->run_test();

	TRACE_LINE(L"Logging results...");
	results_logger->log_results({ });
}

thread_comparison_with_contention::thread_comparison_with_contention(p_log_results const & results_logger, p_test_thread_factory const & thread_factory) noexcept :
	m_results_logger { results_logger },
	m_thread_factory { thread_factory }
{}

auto thread_comparison_with_contention::run_test() const -> void
{
	auto terminate = false;
	auto background_work = multi_threading::create_background_worker(add_background_noise, 100, terminate);

	run_comparison_test(m_results_logger, m_thread_factory, terminate);
}