// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "pthread.h"
#include "semaphore.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "time.h"
#include <conio.h>
#include "Monitor.h"

using namespace std;

Monitor monitor;

void *Producer(void *arg)
{
	int value;
	do
	{
		value = rand() % 100;
		cout << "Wyprodukowano: " << value << endl;
		Message message(value);
		monitor.put(message);
		Sleep(rand() % 5);
	} while(value);

	pthread_exit(NULL);

	return 0;
}

void *Consumer(void *arg)
{
	int value;

	do
	{
		int threadId = (int)arg;
		value = monitor.get(threadId);
		cout << "Watek: " << threadId << " Pobrano: " << value << endl;
		Sleep(rand() % 50);
	} while (value);

	pthread_exit(NULL);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	pthread_t prod;
	pthread_t consumers[3];

	srand(time(0));

	for (int i = 0; i < CONSUMER_COUNT; ++i)
	{
		pthread_create(&consumers[i], NULL, Consumer, (void*)i);
	}

	pthread_create(&prod, NULL, Producer, NULL);

	pthread_join(prod, NULL);
	for (int i = 0; i < CONSUMER_COUNT; ++i)
	{
		pthread_join(consumers[i], NULL);
	}
	//pthread_join(cons, NULL);

	_getch();
	return 0;
}

