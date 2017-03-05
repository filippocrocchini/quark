#pragma once
#include <queue>
#include <mutex>

template<typename T>
class SharedQueue {
public:
	int maxSize = 0;
	
	SharedQueue(int size) : maxSize(size) {}
	SharedQueue() : SharedQueue(0) {}

	void setMaxSize(int size)
	{
		this->maxSize = size;
	}

	bool peek(T* ptr) {
		std::unique_lock<std::mutex> lock(mtx);
		if (!queue.empty()) {
			*ptr = queue.front();
			return true;
		}
		return false;
	}

	bool pop(T *ptr) {
		std::unique_lock<std::mutex> lock(mtx);
		if (queue.size() > 0) {
			*ptr = queue.front();
			queue.pop();
			return true;
		}
		return false;
	}

	bool push(T val) {
		std::unique_lock<std::mutex> lock(mtx);

		if (queue.size() > maxSize)
			return false;
	
		queue.push(val);
		return true;
	}

	int size() {
		std::unique_lock<std::mutex> lock(mtx);
		return queue.size();
	}

	bool empty() {
		std::unique_lock<std::mutex> lock(mtx);
		return queue.empty();
	}
private:
	std::mutex mtx;
	std::queue<T> queue;
};