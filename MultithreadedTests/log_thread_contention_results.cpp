#include "log_thread_contention_results.h"
#include "file_builder.h"
#include "thread_contention_format.h"
#include "thread_contention_handle.h"

auto get_value_at_index(std::vector<std::string> const & values, unsigned index) -> std::string
{
	if (values.size() > index) return values[index];
	return "";
}

auto remove_new_line(std::string token) -> std::string
{
	auto position = token.find("\n");

	if (std::string::npos != position) token.erase(token.length() - position, token.length());

	return token;
}

template <typename F>
auto split_string(std::string line, std::string const & delimiter, thread_contention_handle & contention_results, F add_value) -> void
{
	auto position = 0;
	auto token = std::string { };
	auto values = std::vector<std::string> { };

	while ((position = line.find(delimiter)) != std::string::npos)
	{
		token = line.substr(0, position);
		values.push_back(remove_new_line(token));
		line.erase(0, position + delimiter.length());
	}

	if (line.size() > 0) values.push_back(remove_new_line(line));

	contention_results.set_iteration(get_value_at_index(values, 0) + ", ");
	add_value(contention_results, get_value_at_index(values, 1));
}

template <typename F>
auto read_file(thread_contention_format & format_results, std::string const & file, F add_value) -> void
{
	auto infile = std::ifstream { file.c_str() };
	auto line = std::string { };

	std::getline(infile, line);

	while (std::getline(infile, line))
	{
		auto contention_results = thread_contention_handle { };

		split_string(line, ", ", contention_results, add_value);
		format_results.add_values(std::make_shared<thread_contention_handle>(contention_results));
	}
}

log_thread_contention_results::log_thread_contention_results(std::string const & file) noexcept :
	m_file { file }
{}

auto log_thread_contention_results::log_results(std::map<unsigned long long, float> const &) const -> void
{
	auto format_results = thread_contention_format { "Number Of Iterations, Thread-Class Time, Pool-Thread Time" };

	read_file(format_results, "thread-pool-results.txt", [](thread_contention_handle & contention_results, std::string const & value)
	{ 
		contention_results.set_thread_pool_value(value + "\n"); 
	});
	read_file(format_results, "thread-class-results.txt", [](thread_contention_handle & contention_results, std::string const & value)
	{
		contention_results.set_thread_class_value(value + ", ");
	});

	auto builder = std::make_shared<file_builder>(m_file);
	auto const & values = format_results.get_values();

	builder->append_with_new_line(format_results.get_header());

	for (auto value : values)
	{
		auto const & results = *value.second;

		builder->append(results.get_iterations())->append(results.get_thread_class_values())->append(results.get_thread_pool_values());
	}
}