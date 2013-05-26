#include "stdafx.h"
#include "Monitor.h"

Monitor::Monitor()
{
	nr_msg = tail = head = 0;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&not_full, NULL);
	pthread_cond_init(&not_empty, NULL);
}

Monitor::~Monitor()
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&not_full);
	pthread_cond_destroy(&not_empty);
}

void Monitor::put(const int value)
{
	pthread_mutex_lock(&mutex);

	if (nr_msg == SIZE)
		pthread_cond_wait(&not_full, &mutex);

	msgs[tail] = value;
	nr_msg++;
	tail = (tail + 1) % SIZE;


	pthread_cond_signal(&not_empty);
	pthread_mutex_unlock(&mutex);
}

int Monitor::get()
{
	pthread_mutex_lock(&mutex); /* lock a mutex */
	/* the queue is empty - wait for products in the queue */
	if (nr_msg == 0)
		pthread_cond_wait(&not_empty, &mutex);
	int value = msgs[head]; /* take a value from the queue */
	nr_msg--;
	head = (head + 1) % SIZE;
	pthread_cond_signal(&not_full); /* signal free place in the queue */
	pthread_mutex_unlock(&mutex); /* release a mutex */
	return value;
}