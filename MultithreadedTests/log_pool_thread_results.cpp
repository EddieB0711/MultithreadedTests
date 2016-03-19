#include "log_pool_thread_results.h"
#include "file_builder.h"

log_pool_thread_results::log_pool_thread_results(std::string const & file, std::string const & header) noexcept :
	m_file { file },
	m_header { header }
{}

auto log_pool_thread_results::log_results(std::map<unsigned long long, float> const & results) const -> void
{
	auto builder = std::make_shared<file_builder>(m_file);

	builder->append_with_new_line(m_header);

	for (auto result : results) builder->append_with_separator(result.first)->append_with_new_line(result.second);
}