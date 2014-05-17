#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"
#include "queue_len.h"

// выдаёт ответ в след формате: res[0] - номер узла, из которого вытащить, res[1] - в который вставить
int* analysis1(Processing_Struct State[4]){	
	int res[2];
	long a[4];
	int i;
	for (i=0;i<4;i++){
		if (i<2) {a[i] =(queue_len(State[i], 1)/State[i].Block_D1.size());}
		else {    a[i] =(queue_len(State[i], 0)/State[i].Block_D1.size());}
	}
	
	int largest = -1;
	int lowest = 0;
	long max = -1;
	long min = a[0];

	for (i=0;i<4;i++){
		if (a[i] > max){largest = i; max = a[i];}
		if (a[i]<min){lowest = i; min = a[i];}
	}

	if ((max != min)&&(State[lowest].Block_D1.size() != 1)){
			res[0] = lowest;
			res[1] = largest;
	}
	else{
		res[0] = -1;
		res[1] = -1;
	}
	return res;
}