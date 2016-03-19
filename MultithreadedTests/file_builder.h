#pragma once

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
	auto append(T const & value) noexcept -> file_builder *
	{
		m_file << value;
		return this;
	}

	template <typename T>
	auto append_with_separator(T const & value) noexcept -> file_builder *
	{
		m_file << value << ", ";
		return this;
	}

	template <typename T>
	auto append_with_new_line(T const & value) noexcept -> file_builder *
	{
		m_file << value << "\n";
		return this;
	}
};