#include "environment_handle.h"

namespace multi_threading
{
	environment_handle::environment_handle() noexcept
	{
		InitializeThreadpoolEnvironment(&m_handle);
	}

	environment_handle::~environment_handle() noexcept
	{
		DestroyThreadpoolEnvironment(&m_handle);
	}

	auto environment_handle::get() noexcept -> PTP_CALLBACK_ENVIRON
	{
		return &m_handle;
	}
}