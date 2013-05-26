// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <conio.h>
#include <iostream>
#include "semaphore.h"
#include <time.h>

using namespace std;

//int x, y, a, b;
//
//void *start_routine(void *i)
//{
//	a = x + 2;
//	b = a * y;
//	return (void*)1;
//}

int total = 0;

void *start_routine(void *i)
{
	int a = 0;
	for (int i = 0; i < 10000000; ++i)
	{
		total += 1;
	}

	return (void*)a;
}

#define SIZE 10
int buffer[SIZE];
sem_t addToBufer, removeFromBufer;
int addPointer = 0, removePointer = 0;

void *AddToBufor(void* i)
{
	sem_wait(&addToBufer);
	cout << "Dodaje: " << (int)i << endl;
	buffer[addPointer] = (int)i;
	addPointer = (addPointer + 1) % SIZE;
	sem_post(&removeFromBufer);

	for (int z = 0; z < 1000000000; ++z) 
	{
		z *= z;
	}

	pthread_exit(NULL);
	return NULL;
}


void *GetFromBufor(void*)
{
	sem_wait(&removeFromBufer);
	int abc = buffer[removePointer];
	cout << "Wyciagam: " << abc << endl;
	removePointer = (removePointer + 1) % SIZE;
	sem_post(&addToBufer);	

	pthread_exit(NULL);
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*pthread_t tid;
	x = 2;
	pthread_create(&tid, NULL, start_routine, (void*)1);
	y = 3;
	int value;
	pthread_join(tid, (void **)&value);

	cout << "a = " << a << " b = " << b << " x = " << x << " y = " << y << " zwraca = " << value;*/

	//pthread_t tid;
	//pthread_create(&tid, NULL, start_routine, (void*)1);
	/*for (int i = 0; i < 10000000; ++i)
	{
		total += 1;
	}
	int value;
	pthread_join(tid, (void **)&value);*/

	pthread_t producerThread[10];
	pthread_t consumerThread[10];
	
	sem_init(&addToBufer, 0, SIZE);
	sem_init(&removeFromBufer, 0, 0);

	for (int i = 0; i < 10; ++i)
	{
		cout << "Tworze watek producenta: " << i << endl;
		pthread_create(&producerThread[i], NULL, AddToBufor, (void*)i);
		cout << "Tworze watek konsumenta: " << i << endl;
		pthread_create(&consumerThread[i], NULL, GetFromBufor, NULL);
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << "Czekam na producenta: " << i << endl;
		pthread_join(producerThread[i], NULL);
		cout << "Czekam na konsumenta: " << i << endl;
		pthread_join(consumerThread[i], NULL);		
	}


	
	_getch();
	return 0;
}

