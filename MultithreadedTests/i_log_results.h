#pragma once

#include <vector>

struct i_log_results
{
	virtual auto log_results(unsigned long long iterations, std::vector<float> const & durations) const -> void = 0;

	virtual ~i_log_results() {}
};