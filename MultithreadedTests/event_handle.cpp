#include "event_handle.h"

namespace multi_threading
{
	event_handle::event_handle(event_type type) :
		m_handle { CreateEvent(nullptr, static_cast<BOOL>(type), false, nullptr) }
	{
		if (!m_handle) throw windows_exception();
	}

	event_handle::event_handle(event_handle && other) noexcept :
		m_handle { other.m_handle.release() }
	{}

	auto event_handle::operator =(event_handle && other) noexcept -> event_handle &
	{
		m_handle = std::move(other.m_handle);
		return *this;
	}

	auto event_handle::set() noexcept -> void
	{
		ASSERT(FALSE != SetEvent(m_handle.get()));
	}

	auto event_handle::clear() noexcept -> void
	{
		ASSERT(FALSE != ResetEvent(m_handle.get()));
	}

	auto event_handle::wait(DWORD const milliseconds) noexcept -> bool
	{
		const auto result = WaitForSingleObject(m_handle.get(), milliseconds);

		return result == WAIT_OBJECT_0;
	}

	auto event_handle::get() const noexcept -> HANDLE
	{
		return m_handle.get();
	}
}