#pragma once

#include <map>

class thread_contention_handle;

class thread_contention_format
{
	using values_collection = std::map<std::string, std::shared_ptr<thread_contention_handle>>;

	std::string m_header;
	values_collection m_values;

public:
	explicit thread_contention_format(std::string const & header) noexcept;

	auto add_values(std::shared_ptr<thread_contention_handle> const & value) -> void;

	auto get_header() const noexcept -> std::string;
	auto get_values() const noexcept -> values_collection;
};