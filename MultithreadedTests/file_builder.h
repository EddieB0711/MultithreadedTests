#pragma once

#include <string>
#include <fstream>

class file_builder
{
	std::ofstream m_file;

public:
	file_builder(file_builder const &) = delete;
	auto operator =(file_builder const &) -> file_builder & = delete;

	explicit file_builder(std::string const & file);

	~file_builder() noexcept;

	template <typename T>
	auto append(T const & value, bool with_seperator = true) noexcept -> file_builder &
	{
		m_file << value;
		if (with_seperator) m_file << ", ";

		return *this;
	}
};