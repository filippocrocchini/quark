#include "core/threads/mythread.h"

Thread::Thread(ThreadLoop &looper): looper(&looper){}

void Thread::start() {
	worker = new std::thread(
	[](ThreadLoop *looper) {
		looper->loop();
	}, looper);
}

void Thread::join() {
	worker->join();
	delete worker;
}

