#include "pool_thread_tests.h"
#include "i_log_results.h"
#include "thread_environment.h"
#include "multi_thread_test_utils.h"

using namespace multi_threading;
using namespace timing;

using result_values = std::map<unsigned long long, float>;

auto __stdcall run_long_process(PTP_CALLBACK_INSTANCE, void * args, PTP_WORK) -> void
{
	auto const & threading_work = *reinterpret_cast<multi_threaded_work *>(args);
	auto const & current_iterations = threading_work.iterations();
	auto const & upper_bound = current_iterations.upper_bound();
	auto const & lower_bound = current_iterations.lower_bound();

	TRACE(L"running iteration: %d\n", threading_work.work());

	for (auto i = 0; i < upper_bound; ++i)
		for (auto j = 0; j < lower_bound; ++j);
}

auto run_pool_test(std::vector<multi_threaded_work> & work, thread_environment & thread) -> void
{
	for (auto & w : work) thread.submit(run_long_process, &w);
	thread.wait();
}

auto run_pool_threaded_tests(bounded_iterations current_iterations, thread_environment & thread, result_values & results) -> void
{
	auto work = std::vector<multi_threaded_work> { };

	for (auto i = 1; i <= current_iterations.work(); ++i) work.push_back(multi_threaded_work { i, current_iterations });

	auto duration = time_seconds::time(run_pool_test, work, thread);

	TRACE(L"run_pool_threaded_tests took: %f\n", duration);

	results.insert(result_values::value_type(current_iterations.total_iterations(), duration));
}

pool_thread_tests::pool_thread_tests(p_log_results const & results_logger) noexcept :
	m_results_logger { results_logger }
{}

auto pool_thread_tests::run_test() const -> void
{
	auto const & iterations = test_iterations();
	auto results = result_values { };
	auto thread = std::make_shared<multi_threading::thread_environment>();

	for (auto const & iter : iterations) run_pool_threaded_tests(create_bounded_iterations(iter), *thread, results);
	
	m_results_logger->log_results(results);
}