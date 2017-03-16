#pragma once
#include "core/threads/mythread.h"

class UpdateManager : public ThreadLoop{
public:
	void loop();
};

/*
namespace eng {
	namespace update_manager {
		extern std::thread* thread;

		extern void start();
		extern void join();

		extern void updateThreadMain();
	}
}
*/