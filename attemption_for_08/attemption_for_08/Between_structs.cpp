#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"

Processing_Struct Between_structs(Processing_Struct Struct1, Processing_Struct Struct2) {
		if (Struct1.a6.back()!=Struct2.a1.back())
		{
				Struct2.a1.push_back(Struct1.a6.back());
		}
	
		return Struct2;
}