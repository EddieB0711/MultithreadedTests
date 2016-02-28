#pragma once

struct i_test_threads
{
	virtual auto run_test() const -> void = 0;

	virtual ~i_test_threads() {}
};