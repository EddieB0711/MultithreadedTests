#include "multi_threaded_work.h"

multi_threaded_work::multi_threaded_work(int work, bounded_iterations const & current_iterations) noexcept :
	m_work { work },
	m_current_iterations { current_iterations }
{}

auto multi_threaded_work::work() const noexcept -> int
{
	return m_work;
}

auto multi_threaded_work::iterations() const noexcept -> bounded_iterations
{
	return m_current_iterations;
}

auto create_bounded_iterations(int work) -> bounded_iterations
{
	return bounded_iterations { 20000, 25000, work };
}