#pragma once

#include <queue>

class thread_contention_handle
{
	std::string m_iterations;
	std::string m_thread_class_values;
	std::string m_thread_pool_values;

public:
	auto set_iteration(std::string const & iteration) noexcept -> void;
	auto set_thread_class_value(std::string const & value) noexcept -> void;
	auto set_thread_pool_value(std::string const & value) noexcept -> void;

	auto get_iterations() const noexcept -> std::string;
	auto get_thread_class_values() const noexcept -> std::string;
	auto get_thread_pool_values() const noexcept -> std::string;
};