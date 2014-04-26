// ‘”Ќ ÷»я, выдающ€€ рандомное число от 0 до 1 с шагом 0.01
#include "fRand.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

	double fRand()
	{
		int	useless_t = 1 + rand()%100;
		double f = (double)useless_t /100;
		return f; 
	}
//------------------------------------------------------------------------------