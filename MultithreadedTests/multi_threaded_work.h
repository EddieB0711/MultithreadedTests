#pragma once

#include "bounded_iterations.h"

class multi_threaded_work
{
	int m_work;
	bounded_iterations m_current_iterations;

public:
	multi_threaded_work(int work, bounded_iterations const & current_iterations) noexcept;

	auto work() const noexcept -> int;

	auto iterations() const noexcept -> bounded_iterations;
};
