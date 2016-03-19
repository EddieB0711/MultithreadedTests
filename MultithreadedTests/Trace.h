#pragma once

#include <stdio.h>
#include <crtdbg.h>

#define ASSERT _ASSERTE

#ifdef _DEBUG
struct Tracer
{
	char const * m_filename;
	unsigned m_line;
	std::wstring m_line_ending;

	Tracer(char const * filename, unsigned const line, wchar_t const * line_ending) :
		m_filename { filename },
		m_line { line },
		m_line_ending { line_ending }
	{}

	template <typename... Args>
	auto operator()(wchar_t const * format, Args... args) const -> void
	{
		wchar_t buffer[256];
		auto formatted_text = std::wstring { format };
		formatted_text += m_line_ending;

		auto count = swprintf_s(buffer,
								L"%S(%d): ",
								m_filename,
								m_line);

		ASSERT(-1 != count);
		
		ASSERT(-1 != _snwprintf_s(buffer + count,
						          _countof(buffer) - count,
							      _countof(buffer) - count - 1,
							      formatted_text.c_str(),
							      args...));

		OutputDebugString(buffer);
	}
};
#endif

#ifdef _DEBUG
#define TRACE Tracer(__FILE__, __LINE__, L"")
#define TRACE_LINE Tracer(__FILE__, __LINE__, L"\n")
#else
#define TRACE __noop
#define TRACE_LINE __noop
#endif