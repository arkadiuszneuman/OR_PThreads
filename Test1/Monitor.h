#include "pthread.h"
#include "Message.h"
#include <iostream>

using namespace std;

class Monitor
{
private:
	Message *msgs[SIZE];
	int heads[CONSUMER_COUNT];
	int tail, head;
	int nr_msg;

	pthread_cond_t not_full;
	pthread_cond_t not_empty;
	pthread_mutex_t mutex;

public:
	Monitor();
	~Monitor();
	void put(Message *value);
	int get(int threadId);
};