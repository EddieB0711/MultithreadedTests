#pragma once

#include "i_log_results.h"

class log_pool_thread_results : public i_log_results
{
	std::string const m_file;

public:
	explicit log_pool_thread_results(std::string const & file) noexcept;

	virtual auto log_results(unsigned long long iterations, std::vector<float> const & durations) const -> void;
};