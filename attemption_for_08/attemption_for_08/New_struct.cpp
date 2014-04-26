#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"

Processing_Struct New_struct(int n, double dT) {
		int i;
		Processing_Struct MAIN_struct;
		for (i=0; i<n; i++)
		{
			MAIN_struct.Block_D1.push_back(0);
			MAIN_struct.W1.push_back(0);
		}
		MAIN_struct.Block_D2.push_back(0);
		MAIN_struct.T_start = 0;
		MAIN_struct.T_end = dT;
		MAIN_struct.W2.push_back(0);

		return MAIN_struct;
}