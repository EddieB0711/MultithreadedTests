#pragma once

#include "i_test_threads.h"
#include "p_log_results.h"

class thread_class_tests : public i_test_threads
{
	p_log_results const m_results_logger;

public:
	explicit thread_class_tests(p_log_results const & results_logger) noexcept;

	virtual auto run_test() const -> void;
};