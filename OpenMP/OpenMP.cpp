
#include "stdafx.h"
#include <conio.h>
#include <omp.h>
#include <iostream>

#define NUM_THREADS 30

static long num_steps = 10000000000;
double step;

double Parallel()
{
	double sum[NUM_THREADS];
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel 
	{
		int i;
		double x;     
		int id; 
		id = omp_get_thread_num();
		for (i = id, sum[id] = 0.0; i < num_steps; i = i + NUM_THREADS)
		{ 
			x = (i+0.5)*step; 
			sum[id] += 4.0/(1.0+x*x); 
		} 
	}

	int i;
	double pi;
	for(i=0, pi=0.0; i<NUM_THREADS; i++)
		pi += sum[i] * step; 

	return pi;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double pi = Parallel();
	std::cout.precision(50);
	std::cout << pi << std::endl;
	_getch();

	return 0;
}

