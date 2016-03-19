#pragma once

#include "p_test_threads.h"

enum class test_thread_type
{
	pool_thread,
	thread_class,
	compare_with_contention
};

struct i_test_thread_factory
{
	virtual auto create_thread_test(test_thread_type test_type) noexcept -> p_test_threads = 0;
	virtual ~i_test_thread_factory() {}
};