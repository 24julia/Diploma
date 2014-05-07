#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"
using namespace std;

Processing_Struct reduce_d1 (Processing_Struct one){
	vector<long>::const_iterator lowest = min_element( one.W1.begin(), one.W1.end() );
	if (*lowest > 0) {cout<< one.Block_D1[0]<<"here"<< one.Block_D1[1] <<endl; return one;}
	else{// есть свободное устройство
		vector<long>::const_iterator lowest2 = lowest-one.W1.begin()+one.Block_D1.begin();
		one.W1.erase(lowest);
		one.Block_D1.erase(lowest2);
		one.n = -1;
		return one;
	}
}
