#include "thread_contention_format.h"
#include "thread_contention_handle.h"

auto update_if_empty(thread_contention_handle const & source, thread_contention_handle & destination) -> void
{
	if (!source.get_iterations().empty()) destination.set_iteration(source.get_iterations());
	if (!source.get_thread_class_values().empty()) destination.set_thread_class_value(source.get_thread_class_values());
	if (!source.get_thread_pool_values().empty()) destination.set_thread_pool_value(source.get_thread_pool_values());
}

thread_contention_format::thread_contention_format(std::string const & header) noexcept :
	m_header { header }
{}

auto thread_contention_format::add_values(std::shared_ptr<thread_contention_handle> const & value) -> void
{
	auto iterator = m_values.find(value->get_iterations());

	if (iterator != m_values.end()) update_if_empty(*value, *(iterator->second));
	else m_values.insert(values_collection::value_type(value->get_iterations(), value));
}

auto thread_contention_format::get_header() const noexcept -> std::string
{
	return m_header;
}

auto thread_contention_format::get_values() const noexcept -> values_collection
{
	return m_values;
}