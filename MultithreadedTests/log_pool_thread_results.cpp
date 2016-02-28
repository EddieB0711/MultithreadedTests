#include "log_pool_thread_results.h"
#include "file_builder.h"

log_pool_thread_results::log_pool_thread_results(std::string const & file) noexcept :
	m_file { file }
{}

auto log_pool_thread_results::log_results(unsigned long long iterations, std::vector<float> const & durations) const -> void
{
	auto && builder = file_builder { m_file };

	builder.append(iterations);

	for (auto & iter = durations.begin(); iter != durations.end(); ++iter)
	{
		if (iter + 1 != durations.end()) builder.append(*iter);
		else builder.append(*iter, false).append("\n", false);
	}
}