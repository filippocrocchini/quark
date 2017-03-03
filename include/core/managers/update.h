#pragma once
#include <thread>

class UpdateManager {
public:
	std::thread* thread;

	UpdateManager() = default;

	void start();
	void join();
private:
	static void updateThreadMain(UpdateManager* self);
};