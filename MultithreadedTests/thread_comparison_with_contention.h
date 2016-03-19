#pragma once

#include "i_test_threads.h"
#include "p_log_results.h"
#include "p_test_thread_factory.h"

class thread_comparison_with_contention : public i_test_threads
{
	p_log_results const m_results_logger;
	p_test_thread_factory const m_thread_factory;

public:
	thread_comparison_with_contention(p_log_results const & results_logger, p_test_thread_factory const & thread_factory) noexcept;

	virtual auto run_test() const -> void;
};