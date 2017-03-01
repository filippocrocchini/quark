#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <functional>

#define TASK_QUEUED 0
#define TASK_FREE 1
#define TASK_EXECUTED 2
#define TASK_FAILED 3

class Task {
public:
	int status = TASK_FREE;
	virtual void execute() = 0;
};

class ThreadPool {
public:
	ThreadPool(uint32_t poolSize);
	~ThreadPool();
	
	void submit(Task* t);

private:
	//Create thread safe queue: http://stackoverflow.com/questions/36762248/why-is-stdqueue-not-thread-safe
	//std::queue<Task*> task_queue;
	std::vector<std::thread> threads;

	Task* consume();
};