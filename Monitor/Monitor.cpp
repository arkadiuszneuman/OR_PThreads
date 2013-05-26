#include "stdafx.h"
#include "Monitor.h"

Monitor::Monitor()
{
	nr_msg = tail = head = 0;

	for (int i = 0; i < SIZE; ++i)
	{
		msgs[i] = NULL;
	}

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

void Monitor::put(Message *value)
{
	pthread_mutex_lock(&mutex);
	Message *message = msgs[tail];

	if (message != NULL && !message->allRead())
	{
		cout << "Czekam - producent" << endl;
		pthread_cond_wait(&not_full, &mutex);
	}

	if (message != NULL)
		cout << "Producent: w miejsce " << message->getMsg() << " wstawiam " << value->getMsg() << endl;
	delete message;
	msgs[tail] = value;	
	tail = (tail + 1) % SIZE;

	pthread_cond_signal(&not_empty);
	pthread_mutex_unlock(&mutex);
}

int Monitor::get(int threadId)
{
	pthread_mutex_lock(&mutex);
	Message *testMessage = msgs[heads[threadId]];

	if (testMessage == NULL || testMessage->isRead(threadId))
	{
		cout << "Czekam - konsument " << threadId << endl;
		pthread_cond_wait(&not_empty, &mutex);
	}
	
	Message *message = msgs[heads[threadId]];
	int value = message->getMsg();		
	message->setRead(threadId);
	heads[threadId] = (heads[threadId] + 1) % SIZE;

	if (message->allRead())
		pthread_cond_signal(&not_full);

	pthread_mutex_unlock(&mutex);

	return value;
}