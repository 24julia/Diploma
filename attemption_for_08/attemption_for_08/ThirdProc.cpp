//�������, ����������� ��������� ������� �����, ��������� �������� �� ������� �������
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "ThirdProc.h"
#include "Poison.h"	
#include "Processing_Func.h"
#include "GLOBAL_CONST.h"
using namespace std;

	Processing_Struct ThirdProc(Processing_Struct one, float lambda1) 
	{
		// ����������� ������ ������� �������
			long element;
			element = one.a3[0];
			one.a3.erase( one.a3.begin( ) );
			// �������� ����������� �������, ��������� O(n)
			vector<long>::const_iterator lowest = min_element( one.Block_D1.begin(), one.Block_D1.end() );
			int min_number;
			min_number = lowest - one.Block_D1.begin();
			// �������� ����������� ������� �� ����� ��������� ������� + ������������� ��
			if (element < one.Block_D1[min_number])
			{ 
				one.Block_D1[min_number] = one.Block_D1[min_number] + Poison(lambda1);
				one.W1[min_number] = 3;

			}
			else
			{
				one.Block_D1[min_number] = element + Poison (lambda1);
				one.W1[min_number] = 3;

			}


			return one;
		
	}
//-----------------