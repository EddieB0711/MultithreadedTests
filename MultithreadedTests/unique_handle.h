#pragma once

#include "handle_traits.h"

namespace multi_threading
{
	struct windows_exception
	{
		DWORD error;

		windows_exception(DWORD error = GetLastError()) :
			error { error }
		{}
	};

	template <typename Traits>
	class unique_handle
	{
		using pointer = typename Traits::pointer;

		pointer m_value;

		auto close() noexcept -> void
		{
			if (*this)
			{
				Traits::close(m_value);
			}
		}

	public:
		unique_handle(unique_handle const &) = delete;
		auto operator =(unique_handle const &) -> unique_handle & = delete;

		explicit unique_handle(pointer value = Traits::invalid()) noexcept :
			m_value { value }
		{}

		unique_handle(unique_handle && other) noexcept :
			m_value { other.release() }
		{}

		~unique_handle() noexcept
		{
			close();
		}

		auto operator =(unique_handle && other) noexcept -> unique_handle &
		{
			if (this != &other)
			{
				reset(other.release());
			}

			return *this;
		}

		explicit operator bool() const noexcept
		{
			return m_value != Traits::invalid();
		}

		auto get() const noexcept -> pointer
		{
			return m_value;
		}

		auto reset(pointer value = Traits::invalid()) noexcept -> bool
		{
			if (m_value != value)
			{
				close();
				m_value = value;
			}

			return static_cast<bool>(*this);
		}

		auto release() noexcept -> pointer
		{
			auto value = m_value;

			m_value = Traits::invalid();

			return value;
		}
	};

	using null_handle = unique_handle<null_traits>;
	using pool_handle = unique_handle<pool_traits>;
	using cleanupgroup_handle = unique_handle<cleanupgroup_traits>;
}