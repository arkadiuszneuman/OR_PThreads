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

#define CONSUMER_COUNT 1;

using namespace std;

Monitor monitor;

void *Producer(void *arg)
{
	int value;
	do
	{
		value = rand() % 100;
		cout << "Wyprodukowano: " << value << endl;
		monitor.put(value);
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
		value = monitor.get();
		cout << "Watek: " << threadId << " Pobrano: " << value << endl;
		Sleep(rand() % 5);
	} while (value);

	pthread_exit(NULL);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	pthread_t prod;
	pthread_t consumers[3];

	srand(time(0));

	pthread_create(&prod, NULL, Producer, NULL);
	//pthread_create(&cons, NULL, Consumer, NULL);

	for (int i = 0; i < 3; ++i)
	{
		pthread_create(&consumers[i], NULL, Consumer, (void*)i);
	}

	pthread_join(prod, NULL);
	for (int i = 0; i < 3; ++i)
	{
		pthread_join(consumers[i], NULL);
	}
	//pthread_join(cons, NULL);

	_getch();
	return 0;
}
