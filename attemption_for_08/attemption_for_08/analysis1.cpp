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
std::vector<int> analysis1(Processing_Struct struct1, Processing_Struct struct2, Processing_Struct struct3, Processing_Struct struct4){	
	std::vector<int> res;
	std::vector<long> a;
	a.push_back(queue_len(struct1, 1)/struct1.Block_D1.size());
	a.push_back(queue_len(struct2, 0)/struct2.Block_D1.size());
	a.push_back(queue_len(struct3, 0)/struct3.Block_D1.size());
	a.push_back(queue_len(struct4, 0)/struct4.Block_D1.size());

	std::vector<long>::const_iterator largest = max_element(a.begin(), a.end());
	std::vector<long>::const_iterator lowest  = min_element(a.begin(), a.end());

	if (*largest != *lowest){		
		res.push_back(lowest -a.begin());
		res.push_back(largest-a.begin());
	}
	else{
		res.push_back(0);
		res.push_back(0);
	}
	return res;
}