#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"
using namespace std;

Processing_Struct increase_d1 (Processing_Struct one)
{	one.W1.push_back(0);
	one.Block_D1.push_back(0);
	return one;
}
