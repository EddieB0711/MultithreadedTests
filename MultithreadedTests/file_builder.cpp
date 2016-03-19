#include "file_builder.h"

#define SAFE_CLOSE_FILE(file) if (file.is_open()) file.close()

file_builder::file_builder(std::string const & file) :
	m_file { file.c_str(), std::ios::out }
{}

file_builder::~file_builder() noexcept 
{ 
	SAFE_CLOSE_FILE(m_file); 
}