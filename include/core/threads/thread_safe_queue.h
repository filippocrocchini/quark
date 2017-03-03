#pragma once
#include <queue>
#include <mutex>

template<typename T>
class SharedQueue {
public:
	int maxSize = 0;
	void setMaxSize(int);
	bool peek(T*);
	bool pop(T*);
	bool push(T);
	int size();
	bool empty();
private:
	std::mutex mtx;
	std::queue<T> queue;
};