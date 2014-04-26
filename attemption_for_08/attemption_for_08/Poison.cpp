//функци€, генерирующа€ случайную величину, подчин€ющуюс€ распределению ѕуассона.
#include "fRand.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Poison.h"	
long Poison(double lambda)
	{
		/*long k = 0;
		double p = 1;
		double L;
		L = exp(-lambda2);
		while (p > L)
		{
			k++;
			double f = fRand();
			p = p*f;
		}
		return k-1;*/
		return (long) (ceil)(-1*(0.7/lambda)*log(fRand())+0.3/lambda);
	}