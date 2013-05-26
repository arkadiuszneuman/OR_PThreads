
#include "stdafx.h"
#include <conio.h>
#include <omp.h>
#include <iostream>

static long num_steps = 1000000;
double step;

double Parallel()
{
	int i;
	int threads = omp_get_num_threads();
	double x, pi;
	double* sum = new double[threads];
	for (int i = 0; i < threads; ++i)
	{
		sum[i] = 0;
	}
	step = 1.0/(double) num_steps;

#pragma omp parallel 
	{
		double x;     int id; 
		id = omp_get_thread_num();
		for (i=id, sum[id]=0.0;i< num_steps; i=i+threads){ 
			x = (i+0.5)*step; 
			sum[id] += 4.0/(1.0+x*x); 
		} 
	}

	for(i=0, pi=0.0;i<threads;i++)
		pi += sum[i] * step; 

	//delete[] sum;
	//sum = NULL;

	return pi;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double pi = Parallel();

	std::cout << pi << std::endl;
	_getch();

	return 0;
}

