#pragma once

struct i_log_results
{
	virtual auto log_results(std::map<unsigned long long, float> const & results) const -> void = 0;

	virtual ~i_log_results() {}
};