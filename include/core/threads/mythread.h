#pragma once

#include <unordered_set>
#include <thread>

class ThreadLoop{
public:
	virtual void loop() = 0;
};

class Thread{
public:
	ThreadLoop *looper;
	Thread(ThreadLoop &looper);

	void start();
	void join();
private:
	std::thread* worker;
};