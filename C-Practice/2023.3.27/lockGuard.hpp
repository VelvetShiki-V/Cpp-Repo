#ifndef __LOCK_GUARD_HPP
#define __LOCK_GUARD_HPP
#include <iostream>
#include <mutex>

class Mutex {
public:
	Mutex(std::mutex* mutex)
		:mtx(mutex)
	{}
	void lock() {
		mtx->lock();
	}
	void unlock() {
		mtx->unlock();
	}
private:
	std::mutex* mtx;
};

class LockGuard {
public:
	LockGuard(std::mutex* mutex)
		:mtx(mutex)
	{
		mtx.lock();
	}
	~LockGuard() {
		mtx.unlock();
	}

private:
	Mutex mtx;
};

#endif