#pragma once
#include <thread>

namespace eng {
	namespace update_manager {
		extern std::thread* thread;

		extern void start();
		extern void join();

		extern void updateThreadMain();
	}
}