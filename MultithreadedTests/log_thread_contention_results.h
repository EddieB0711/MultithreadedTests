#pragma once

#include "i_log_results.h"

class log_thread_contention_results : public i_log_results
{
	std::string m_file;

public:
	explicit log_thread_contention_results(std::string const & file) noexcept;

	virtual auto log_results(std::map<unsigned long long, float> const &) const -> void;
};