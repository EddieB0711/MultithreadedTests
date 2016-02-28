#pragma once

#include <chrono>

namespace timing
{
	struct seconds
	{
		using ret = float;
		using system_clock = std::chrono::system_clock;

		static auto convert(std::chrono::time_point<system_clock> start) noexcept -> float
		{
			std::chrono::duration<float> duration = system_clock::now() - start;
			return duration.count();
		}
	};

	struct milliseconds
	{
		using ret = std::chrono::milliseconds::rep;
		using system_clock = std::chrono::system_clock;

		static auto convert(std::chrono::time_point<system_clock> start) noexcept -> ret
		{
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now() - start);
			return duration.count();
		}
	};

	template <typename Traits>
	struct time_something
	{
		template <typename F, typename... Args>
		static auto time(F fn, Args &&... args) -> typename Traits::ret
		{
			auto start = Traits::system_clock::now();

			fn(std::forward<Args>(args)...);

			return Traits::convert(start);
		}
	};

	using time_seconds = time_something<seconds>;
	using time_milliseconds = time_something<milliseconds>;
}