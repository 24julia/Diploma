//�������, ����������� ��������� ������� �����, ��������� �������� �� ��������� �������
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

Processing_Struct FourthProc(Processing_Struct one, float lambda2) 
	{
		// ����������� ������ ������� �������
			long element;
			element = one.a4[0];
			one.a4.erase( one.a4.begin( ) );
			// �������� ����������� ������� �� ����� ��������� ������� + ������������� ��
			if (element < one.Block_D2[0])
			{ 
				one.Block_D2[0] = one.Block_D2[0] + Poison(lambda2);
				one.W2[0] = 4;

			}
			else
			{
				one.Block_D2[0] = element + Poison (lambda2);
				one.W2[0] = 4;

			}

			return one;
		
	}