#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>

/**
 * Encargada de encapsular el comportamiento de mutex.
 */
class Mutex{
	private:
		pthread_mutex_t mutex;
	public:
		Mutex();
		~Mutex();

		/**
		 * bloquea el acceso a un objeto.
		 */
		void lock();

		/**
		 * desbloquea el acceso a un objeto.
		 */
		void unlock();
};

class Lock{
public:
	Lock(Mutex &mutex);
	~Lock();
private:
	Mutex& mutex;
};
#endif
