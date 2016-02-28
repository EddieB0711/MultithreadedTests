#pragma once

class bounded_iterations
{
	int const m_upper_bound;
	int const m_lower_bound;
	int const m_work;

public:
	bounded_iterations(int upper_bound, int lower_bound, int work) noexcept;

	auto upper_bound() const noexcept -> int;

	auto lower_bound() const noexcept -> int;

	auto work() const noexcept -> int;

	auto total_iterations() const noexcept -> unsigned long long;
};