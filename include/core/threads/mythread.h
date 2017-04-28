#pragma once

#include <thread>

class ThreadLoop{
public:
	virtual void loop() = 0;
};

class Thread{
public:
	ThreadLoop *looper;
	Thread(ThreadLoop &looper);
	~Thread() {
		if (worker != nullptr)
			delete worker;
	}

	void start();
	void join();
private:
	std::thread* worker;
};
