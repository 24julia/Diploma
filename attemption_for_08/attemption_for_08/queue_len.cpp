#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GLOBAL_CONST.h"
#include "Processing_Func.h"

// ����� ����� � ���� �������: res[0] - ����� ����, �� �������� ��������, res[1] - � ������� ��������
int queue_len(Processing_Struct one, int is_first){	
	if (is_first = 0){
		std::vector<long>::const_iterator largest = max_element(one.a1.begin(), one.a1.end());
		while (*largest>= one.T_end){
			one.a1.erase(largest);
			largest = max_element(one.a1.begin(), one.a1.end());
			};
	}
	return one.a1.size()+one.a3.size()+one.a5.size();
}