//�������, ����������� ��������� ������� �����, ��������� �������� �� ����� �������
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "FifthProc.h"
#include "Poison.h"	
#include "Processing_Func.h"
//#include "GLOBAL_CONST.h"
using namespace std;

	Processing_Struct FifthProc(Processing_Struct one, float lambda1) 
	{
		// ����������� ������ ������� �������
			long element;
			element = one.a5[0];
			one.a5.erase( one.a5.begin( ) );
			// �������� ����������� �������, ��������� O(n)
			vector<long>::const_iterator lowest = min_element( one.Block_D1.begin(), one.Block_D1.end() );
			int min_number;
			min_number = lowest - one.Block_D1.begin();
			// �������� ����������� ������� �� ����� ��������� ������� + ������������� ��
			if (element < one.Block_D1[min_number])
			{ 
				one.Block_D1[min_number] = one.Block_D1[min_number] + Poison(lambda1);
				one.W1[min_number] = 5;

			}
			else
			{
				one.Block_D1[min_number] = element + Poison (lambda1);
				one.W1[min_number] = 5;

			}


			return one;
		
	}
//-----------------