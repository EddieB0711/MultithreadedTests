#pragma once

namespace multi_threading
{
	class environment_handle
	{
		TP_CALLBACK_ENVIRON m_handle;

	public:
		environment_handle(environment_handle const &) = delete;
		environment_handle(environment_handle &&) = delete;
		auto operator =(environment_handle const &) -> environment_handle & = delete;
		auto operator =(environment_handle &&) -> environment_handle & = delete;

		environment_handle() noexcept;

		~environment_handle() noexcept;

		auto get() noexcept -> PTP_CALLBACK_ENVIRON;
	};
}