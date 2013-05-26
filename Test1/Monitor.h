#include "pthread.h"

#define SIZE 10

class Monitor
{
private:
	int msgs[SIZE];
	int tail, head;
	int nr_msg;

	pthread_cond_t not_full;
	pthread_cond_t not_empty;
	pthread_mutex_t mutex;

public:
	Monitor();
	~Monitor();
	void put(const int value);
	int get();
};