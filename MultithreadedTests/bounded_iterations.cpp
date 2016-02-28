#include "bounded_iterations.h"

auto to_big_int(int value) -> unsigned long long
{
	return static_cast<unsigned long long>(value);
}

bounded_iterations::bounded_iterations(int upper_bound, int lower_bound, int work) noexcept :
	m_upper_bound { upper_bound },
	m_lower_bound { lower_bound },
	m_work { work }
{}

auto bounded_iterations::upper_bound() const noexcept -> int
{
	return m_upper_bound;
}

auto bounded_iterations::lower_bound() const noexcept -> int
{
	return m_lower_bound;
}

auto bounded_iterations::work() const noexcept -> int
{
	return m_work;
}

auto bounded_iterations::total_iterations() const noexcept -> unsigned long long
{
	return to_big_int(m_work) * to_big_int(m_upper_bound) * to_big_int(m_lower_bound);
}