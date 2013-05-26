
#include "stdafx.h"
#include <conio.h>
#include <omp.h>
#include <iostream>

// Ustawienie liczby w�tk�w.
#define NUM_THREADS 4

static long num_steps = 1000000000;
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

double OneThread()
{
	int i;
	double x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;
	for (i = 1; i <= num_steps; i++)
	{
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0 + x * x);
	}
	pi = step * sum;

	return pi;
}

double WorkSharingConstruct()
{
	double pi = 0.0;
	double sum[NUM_THREADS]; // tablica sum z powodu wielodost�pu
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		sum[i] = 0.0;
	}

	#pragma omp parallel 
	{
		int i; // osobne i dla ka�dego w�tku z osobna
		int id = omp_get_thread_num(); // numer w�tku
		double x; // zmienna pomocnicza

		// g��wna p�tla
		#pragma omp for
		for (i = 0; i < num_steps; ++i)
		{ 
			x = (i+0.5)*step; 
			sum[id] += 4.0/(1.0 + x * x); 
		} 
	}

	// podliczanie wynik�w cz�stkowych
	for(int i = 0; i < NUM_THREADS; i++) 
	{
		pi += sum[i] * step; 
	}

	return pi;
}

double Reduction()
{
	int i; 	 
	double x, pi, sum = 0.0; 

	step = 1.0/(double) num_steps; 
	omp_set_num_threads(NUM_THREADS); //ustawienie ilo�ci w�tk�w

	#pragma omp parallel for reduction(+:sum) private(x)  //zmienna sum b�dzie sumowana przez w�tki (reduction), oznaczenie zmiennej x jako prywatna
	for (i = 1; i <= num_steps; i++) //g��wna p�tla
	{ 
		x = (i-0.5)*step; 
		sum = sum + 4.0/(1.0 + x * x); 
	} 
	pi = step * sum; 

	return pi;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//wy�wietlenie wynik�w
	std::cout.precision(50);
	std::cout << "Parallel SPMD " << Parallel() << std::endl;
	std::cout << "Work sharing " << WorkSharingConstruct() << std::endl;
	std::cout << "Reduction " << Reduction() << std::endl;

	_getch();

	return 0;
}

