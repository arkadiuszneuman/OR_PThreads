
#include "stdafx.h"
#include <conio.h>
#include <omp.h>
#include <iostream>

// Ustawienie liczby w�tk�w.
#define NUM_THREADS 30

static long num_steps = 10000000000;
double step;

double Parallel()
{	
	double pi = 0.0;
	double sum[NUM_THREADS]; // tablica sum z powodu wielodost�pu
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel 
	{
		int i; // osobne i dla ka�dego w�tku z osobna		
		int id = omp_get_thread_num(); // numer w�tku
		double x; // zmienna pomocnicza

		// g��wna p�tla
		for (i = id, sum[id] = 0.0; i < num_steps; i = i + NUM_THREADS)
		{ 
			x = (i+0.5)*step; 
			sum[id] += 4.0/(1.0+x*x); 
		} 
	}

	// podliczanie wynik�w cz�stkowych
	for(int i = 0; i < NUM_THREADS; i++) 
	{
		pi += sum[i] * step; 
	}

	return pi;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Wy�wietlanie wynik�w.
	std::cout.precision(50);
	std::cout << "Parallel SPMD" << Parallel() << std::endl;
	
	_getch();

	return 0;
}

