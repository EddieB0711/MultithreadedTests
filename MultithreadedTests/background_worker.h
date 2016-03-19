#pragma once

#include <cstddef>
#include <tuple>
#include <functional>

#include "event_handle.h"
#include "thread_environment.h"

namespace multi_threading
{
	enum class pause_durations { no_pause };

	template <std::size_t... Indices> struct indices { };
	template <std::size_t N, std::size_t... Indices> struct build_indices : build_indices<N - 1, N - 1, Indices...> { };
	template <std::size_t... Indices> struct build_indices<0, Indices...> : indices<Indices...> { };
	
	template <typename Args> using tuple_for = build_indices<std::tuple_size<Args>::value>;
	template <typename... Args> struct worker_fn_handle { using worker_fn = std::function<void(Args...)>; };

	template <typename F, typename Arg, std::size_t... Indices>
	auto caller(F const & f, Arg & args, indices<Indices...> const &) -> decltype(f(std::get<Indices>(std::forward<Arg>(args))...))
	{
		return f(std::get<Indices>(std::forward<Arg>(args))...);
	}

	template <typename F, typename Arg>
	auto unpackTuple(F const & f, Arg & args) -> decltype(caller(f, args, tuple_for<Arg> { }))
	{
		return caller(f, args, tuple_for<Arg> { });
	}	

	template <template <typename...> class Aggregate, typename... Args>
	auto __stdcall background_work(PTP_CALLBACK_INSTANCE, void * args, PTP_WORK) -> void
	{
		auto aggregate = *reinterpret_cast<std::shared_ptr<Aggregate<Args...>>*>(args);

		while (!aggregate->get_terminate()) aggregate->perform_work();
	}

	template <typename... Args>
	class background_aggregate
	{
		using worker_fn = typename worker_fn_handle<Args...>::worker_fn;

		bool m_terminate;
		DWORD m_milliseconds;
		event_handle m_event;
		worker_fn m_work;
		std::tuple<Args...> m_args;

	public:
		background_aggregate(worker_fn work, DWORD milliseconds, Args... args) noexcept :
			m_work { work },
			m_milliseconds { milliseconds },
			m_args { std::tie(args...) },
			m_event { event_type::auto_reset },
			m_terminate { false }
		{}

		~background_aggregate() noexcept
		{
			m_terminate = true;
			m_event.set();
		}

		auto perform_work() -> void
		{
			unpackTuple(m_work, m_args);
			m_event.wait(m_milliseconds);
		}

		auto get_terminate() const noexcept -> bool
		{
			return m_terminate;
		}

		auto set_terminate(bool value) noexcept -> void
		{
			m_terminate = value;
		}
	};

	template <typename... Args>
	class background_worker
	{
		using worker_fn = typename worker_fn_handle<Args...>::worker_fn;

		thread_environment m_environment;
		std::shared_ptr<background_aggregate<Args...>> m_aggregate;

	public:
		background_worker(worker_fn work, DWORD milliseconds = static_cast<DWORD>(pause_durations::no_pause), Args... args) :
			m_aggregate { std::make_shared<background_aggregate<Args...>>(work, milliseconds, args...) },
			m_environment { 1 }
		{
			m_environment.submit(background_work<background_aggregate, Args...>, &m_aggregate);
		}

		~background_worker()
		{
			m_aggregate->set_terminate(true);
			m_environment.wait();
		}
	};

	template <typename... Args>
	auto create_background_worker(typename worker_fn_handle<Args...>::worker_fn work, 
								  DWORD milliseconds = static_cast<DWORD>(pause_durations::no_pause), 
								  Args && ... args) -> std::shared_ptr<background_worker<Args...>>
	{
		return std::make_shared<background_worker<Args...>>(work, milliseconds, args...);
	}
}