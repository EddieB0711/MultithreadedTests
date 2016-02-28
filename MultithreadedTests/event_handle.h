#pragma once

#include "unique_handle.h"

namespace multi_threading
{
	enum class event_type
	{
		auto_reset,
		manual_reset
	};

	class event_handle
	{
		null_handle m_handle;

	public:
		event_handle(event_handle const &) = delete;
		auto operator =(event_handle const &) -> event_handle & = delete;

		explicit event_handle(event_type type);

		event_handle(event_handle && other) noexcept;

		auto operator =(event_handle && other) noexcept->event_handle &;

		auto set() noexcept -> void;

		auto clear() noexcept -> void;

		auto wait(DWORD const milliseconds = INFINITE) noexcept -> bool;

		auto get() const noexcept->HANDLE;
	};
}