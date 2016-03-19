#include "thread_contention_handle.h"

auto thread_contention_handle::set_iteration(std::string const & iteration) noexcept -> void
{
	m_iterations = iteration;
}

auto thread_contention_handle::set_thread_class_value(std::string const & value) noexcept -> void
{
	m_thread_class_values = value;
}

auto thread_contention_handle::set_thread_pool_value(std::string const & value) noexcept -> void
{
	m_thread_pool_values = value;
}

auto thread_contention_handle::get_iterations() const noexcept -> std::string
{
	return m_iterations;
}

auto thread_contention_handle::get_thread_class_values() const noexcept -> std::string
{
	return m_thread_class_values;
}

auto thread_contention_handle::get_thread_pool_values() const noexcept -> std::string
{
	return m_thread_pool_values;
}