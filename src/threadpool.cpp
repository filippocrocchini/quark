#include "../headers/threadpool.h"

void threadMain();

ThreadPool::ThreadPool(uint32_t poolSize) {
	threads.reserve(poolSize);
	for (size_t i = 0; i < poolSize; i++) {
		threads.emplace_back(&threadMain);
	}
}

ThreadPool::~ThreadPool() {
	for (auto itr = threads.begin(); itr != threads.end(); itr++) {
		itr->join();
	}
}

void ThreadPool::submit(Task* t) {
	//task_queue.push(t);
	t->status = TASK_QUEUED;
}

Task* ThreadPool::consume() {
	//Task* next = task_queue.front();
	//task_queue.pop();
	//return next;
	return nullptr;
}

void threadMain() {

}