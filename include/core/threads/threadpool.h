#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <exception>
#include <condition_variable>

#include "thread_safe_queue.h"

#define TASK_QUEUED 0
#define TASK_FREE 1
#define TASK_EXECUTED 2
#define TASK_FAILED 3

class Task {
public:
	int status = TASK_FREE;
	void(*execute)(void) = []() {};

	Task(void(*)(void));
};

class ThreadPool {
public:
	ThreadPool(uint32_t, uint32_t);
	~ThreadPool();
	
	void submit(Task*);

	bool running = true;
	bool consume(Task**);

private:
	SharedQueue<Task*> tasks;
	std::vector<std::thread> threads;

	std::mutex mtx;
	std::condition_variable cv;
};