
#include "stdafx.h"
#include <conio.h>
#include <omp.h>

//#pragma omp 

static long num_steps = 100000;
double step;

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	double x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;
	for (i=1; i<= num_steps; i++)
	{
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	pi = step * sum;

	_getch();

	return 0;
}

