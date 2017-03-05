#pragma once
#include <thread>

namespace eng {
	namespace UpdateManager {
		extern std::thread* thread;

		extern void start();
		extern void join();

		extern void updateThreadMain();
	}
}