#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "GLOBAL_CONST.h"
#include "Processing_Func.h"
#include "queue_len.h"

using namespace std;

// выдаёт ответ в след формате: res[0] - номер узла, из которого вытащить, res[1] - в который вставить
int* analysis1(Processing_Struct State[4]){ 
	int res[2];
	double a[4], c;
	int i,j, b[4],c2;
	for (i=0;i<4;i++){
		if (i<2) {a[i] =(queue_len(State[i], 1)/((float)State[i].Block_D1.size()));}
		else { a[i] =(queue_len(State[i], 0)/((float)State[i].Block_D1.size()));}
		b[i] = i;
	}

//cout « "1:"« a[0] « " 2:"« a[1] « " 3:"« a[2] « " 4:"« a[3] « endl;

	int largest = -1;
	int lowest = 0;
	double max = -1;
	double min = a[0];

	for (i=0;i<3;i++){
		for(j=0;j-i;j++){
			if (a[j] > a[j+1]){
				c = a[j];
				a[j] = a[j+1];
				a[j+1] = c;
				c2 = b[j];
				b[j] = b[j+1];
				b[j+1] = c2;
			}
		}
	}


	if (a[3] != a[0]){
		for(i=0;i<3;i++){
			if (State[b[i]].Block_D1.size() != 1){
				res[0] = b[i];
				res[1] = b[3];
				break;
			}
		}
	}
	if ((a[3] == a[0])||((State[b[0]].Block_D1.size() == 1)&&(State[b[1]].Block_D1.size() == 1)&&(State[b[2]].Block_D1.size() == 1))){
		res[0] = -1;
		res[1] = -1;
	}
	return res;
}