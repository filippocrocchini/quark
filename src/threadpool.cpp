#include "../include/core/threads/threadpool.h"
#include "thread_safe_queue.cpp"

#include <iostream>

void threadMain(ThreadPool *);

Task::Task(void(*execute)(void)) {
	this->execute = execute;
}

ThreadPool::ThreadPool(uint32_t poolSize, uint32_t queueSize) {
	tasks.setMaxSize(queueSize);
	threads.reserve(poolSize);
	for (size_t i = 0; i < poolSize; i++) {
		threads.emplace_back(&threadMain, this);
	}
}

ThreadPool::~ThreadPool() {
	for (auto itr = threads.begin(); itr != threads.end(); itr++) {
		itr->join();
	}
}

void ThreadPool::submit(Task* t) {
	tasks.push(t);
	t->status = TASK_QUEUED;
}

bool ThreadPool::consume(Task** task) {	
	return tasks.pop(task);
}

void threadMain(ThreadPool* pool) {
	Task *current;
	while (pool->running) {
		if (!pool->consume(&current)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		} 
		else {
			try {
				current->execute();
			}
			catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				current->status = TASK_FAILED;
				continue;
			}
			current->status = TASK_EXECUTED;
		}
	}
}