#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "GLOBAL_CONST.h"
#include "Processing_Func.h"

// ����� ����� � ���� �������: res[0] - ����� ����, �� �������� ��������, res[1] - � ������� ��������
int queue_len(Processing_Struct one, int is_first){	
	int i;
	int b1 = 0;
	for (i = 0; i<one.a1.size(); i++){
		if (one.a1[i] <= one.T_end){
			b1++;
		}
	}
	return b1+one.a3.size()+one.a5.size();
}