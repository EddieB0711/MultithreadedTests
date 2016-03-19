#include "thread_class_tests.h"
#include "i_log_results.h"
#include "multi_thread_test_utils.h"

#include <thread>

using namespace multi_threading;
using namespace timing;

using result_values = std::map<unsigned long long, float>;

struct join_traits
{
	static auto close(std::thread & thread) -> void
	{
		if (thread.joinable()) thread.join();
	}

	static auto is_valid(std::thread const & thread) -> bool
	{
		return thread.joinable();
	}
};

struct detach_traits
{
	static auto close(std::thread & thread) -> void
	{
		thread.detach();
	}

	static auto is_valid(std::thread const & thread) -> bool
	{
		return thread.joinable();
	}
};

template <typename Traits>
class c_plus_plus_thread_class
{
	std::thread m_thread;

public:
	c_plus_plus_thread_class(c_plus_plus_thread_class const &) = delete;
	auto operator =(c_plus_plus_thread_class const &) -> c_plus_plus_thread_class & = delete;

	template <typename F, typename... Args>
	c_plus_plus_thread_class(F fn, Args &&... args) :
		m_thread { fn, args... }
	{}

	c_plus_plus_thread_class(c_plus_plus_thread_class && other) :
		m_thread { std::move(other.m_thread) }
	{}

	auto operator =(c_plus_plus_thread_class && other) -> c_plus_plus_thread_class &
	{
		if (this != &other) m_thread = std::move(other.m_thread);
		return *this;
	}

	operator bool() const noexcept
	{
		return !Traits::is_valid(m_thread);
	}

	~c_plus_plus_thread_class() 
	{
		Traits::close(m_thread); 
	} // std::thread will call terminate() if it destructs while still joinable, not entirely desirable...
};

using joinable_thread = c_plus_plus_thread_class<join_traits>;
using detachable_thread = c_plus_plus_thread_class<detach_traits>;

class thread_work
{
	std::vector<multi_threaded_work> m_work;

public:
	auto add_work(multi_threaded_work & work) noexcept -> void
	{
		m_work.push_back(work);
	}

	auto get_work() const noexcept -> std::vector<multi_threaded_work>
	{
		return m_work;
	}
};

auto run_thread_class_process(thread_work & threading_work) -> void
{
	auto const & work = threading_work.get_work();

	for (auto & w : work)
	{
		auto const & current_iterations = w.iterations();
		auto const & upper_bound = current_iterations.upper_bound();
		auto const & lower_bound = current_iterations.lower_bound();

		TRACE(L"running iteration: %d\n", w.work());

		for (auto i = 0; i < upper_bound; ++i)
			for (auto j = 0; j < lower_bound; ++j);
	}
}

auto run_thread_class_test(std::vector<thread_work> & work_for_thread) -> void
{
	auto threads = std::vector<joinable_thread> { };
	for (auto & w : work_for_thread) threads.push_back(joinable_thread { run_thread_class_process, std::ref(w) });
}

auto run_thread_class_tests(bounded_iterations current_iterations, result_values & results) -> void
{
	auto work = std::vector<multi_threaded_work> { };
	auto thread_count = get_optimal_threads();
	auto work_for_thread = std::vector<thread_work> { thread_count };

	for (auto i = 1; i <= current_iterations.work(); ++i) work.push_back(multi_threaded_work { i, current_iterations });

	unsigned current_thread = 0;
	for (auto & w : work)
	{
		if (current_thread >= thread_count) current_thread = 0;
		work_for_thread[current_thread].add_work(w);
		++current_thread;
	}

	auto duration = time_seconds::time(run_thread_class_test, work_for_thread);

	TRACE(L"run_thread_class_tests took: %f\n", duration);

	results.insert(result_values::value_type(current_iterations.total_iterations(), duration));
}

thread_class_tests::thread_class_tests(p_log_results const & results_logger) noexcept :
	m_results_logger { results_logger }
{}

auto thread_class_tests::run_test() const -> void
{
	auto const & iterations = test_iterations();
	auto results = result_values { };

	for (auto & iter : iterations) run_thread_class_tests(create_bounded_iterations(iter), results);

	m_results_logger->log_results(results);
}