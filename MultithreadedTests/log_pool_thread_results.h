#pragma once

#include "i_log_results.h"

class log_pool_thread_results : public i_log_results
{
	std::string const m_file;
	std::string const m_header;

public:
	log_pool_thread_results(std::string const & file, std::string const & header) noexcept;

	virtual auto log_results(std::map<unsigned long long, float> const & results) const -> void;
};