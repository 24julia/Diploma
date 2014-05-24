//�������, ����������� ��������� ������� �����, ��������� �������� �� ������ �������.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "FirstProc.h"
#include "Poison.h"	
#include "Processing_Func.h"
//#include "GLOBAL_CONST.h"
using namespace std;

	Processing_Struct FirstProc(Processing_Struct one, float lambda1) 
	{
		// ����������� ������ ������� �������
			long element;
			element = one.a1[0];
			one.a1.erase( one.a1.begin( ) );
			// �������� ����������� �������, ��������� O(n)
			vector<long>::const_iterator lowest = min_element( one.Block_D1.begin(), one.Block_D1.end() );
			int min_number = lowest - one.Block_D1.begin();
			// �������� ����������� ������� �� ����� ��������� ������� + ������������� ��
			if (element < one.Block_D1[min_number])
			{ 
				one.Block_D1[min_number] = one.Block_D1[min_number] + Poison(lambda1);
				one.W1[min_number] = 1;

			}
			else
			{
				one.Block_D1[min_number] = element + Poison (lambda1);
				one.W1[min_number] = 1;

			}


			return one;
		
	}
//--------------------------------------------------------------------------------