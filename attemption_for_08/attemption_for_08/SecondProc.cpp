//�������, ����������� ��������� ������� �����, ��������� �������� ������ �������
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "FirstProc.h"
#include "Poison.h"	
#include "Processing_Func.h"
#include "GLOBAL_CONST.h"
using namespace std;

Processing_Struct SecondProc( Processing_Struct one) 
	{
		// ����������� ������ ������� �������
			long element;
			element = one.a2[0];
			one.a2.erase( one.a2.begin( ) );
			// �������� ����������� ������� �� ����� ��������� ������� + ������������� ��
			if (element < one.Block_D2[0])
			{ 
				one.Block_D2[0] = one.Block_D2[0] + Poison(lambda2);
				one.W2[0] = 2;

			}
			else
			{
				one.Block_D2[0] = element + Poison (lambda2);
				one.W2[0] = 2;

			}

			return one;
		
	}