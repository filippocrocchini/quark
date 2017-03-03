#include "../include/thread_safe_queue.h"

template<typename T>
void SharedQueue<T>::setMaxSize(int size)
{
	this->maxSize = size;
}

template<typename T>
bool SharedQueue<T>::peek(T* ptr) {
	std::unique_lock<std::mutex> lock(mtx);
	if (!queue.empty()) {
		*ptr = queue.front();
		return true;
	}
	return false;
}

template<typename T>
bool SharedQueue<T>::pop(T *ptr) {
	std::unique_lock<std::mutex> lock(mtx);
	if (queue.size() > 0) {
		*ptr = queue.front();
		queue.pop();
		return true;
	}
	return false;
}

template<typename T>
bool SharedQueue<T>::push(T val) {
	std::unique_lock<std::mutex> lock(mtx);

	if (queue.size() > maxSize)
		return false;
	
	queue.push(val);
	return true;
}

template<typename T>
int SharedQueue<T>::size() {
	std::unique_lock<std::mutex> lock(mtx);
	return queue.size();
}

template<typename T>
bool SharedQueue<T>::empty() {
	std::unique_lock<std::mutex> lock(mtx);
	return queue.empty();
}
