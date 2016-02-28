#pragma once

#include <windows.h>

namespace multi_threading
{
	struct null_traits
	{
		using pointer = HANDLE;

		static auto invalid() noexcept -> pointer
		{
			return nullptr;
		}

		static auto close(pointer value) noexcept -> void
		{
			CloseHandle(value);
		}
	};

	struct pool_traits
	{
		using pointer = PTP_POOL;

		static auto invalid() noexcept -> pointer
		{
			return nullptr;
		}

		static auto close(pointer value) noexcept -> void
		{
			CloseThreadpool(value);
		}
	};

	struct cleanupgroup_traits
	{
		using pointer = PTP_CLEANUP_GROUP;

		static auto invalid() noexcept -> pointer
		{
			return nullptr;
		}

		static auto close(pointer value) noexcept -> void
		{
			CloseThreadpoolCleanupGroup(value);
		}
	};
}