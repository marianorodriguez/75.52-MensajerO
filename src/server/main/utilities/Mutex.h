#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>

class Mutex{
	private:
		pthread_mutex_t mutex;
	public:
		Mutex();
		void lock();
		void unlock();
		~Mutex();
};

class Lock{
public:
	Lock(Mutex &mutex);
	~Lock();
private:
	Mutex& mutex;
};
#endif
