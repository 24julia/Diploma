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
	long bussy;
	bussy = *lowest;
	if (bussy > 0) {return one;}
	else{// есть свободное устройство
		one.W1.erase(lowest);
		one.Block_D1.erase(lowest);
		one.n = 0;
		return one;
	}
}
