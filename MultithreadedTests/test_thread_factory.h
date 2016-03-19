#pragma once

#include "i_test_thread_factory.h"

struct test_thread_factory : public i_test_thread_factory, public std::enable_shared_from_this<test_thread_factory>
{
	virtual auto create_thread_test(test_thread_type test_type) noexcept -> p_test_threads;
};