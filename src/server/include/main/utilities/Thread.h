#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>

/**
 * Clase abstracta para crear threads.
 */
class Thread{
public:
	Thread();
	int run();
	void join();
	virtual void runFunction() = 0;
	virtual ~Thread();
protected:
	pthread_mutex_t mutex;
private:
	Thread(const Thread& otherThread);
	const Thread& operator=(const Thread& otherThread);
	pthread_t thread;
	static void* starter(void* arg);
};

#endif
