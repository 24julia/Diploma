// ������� ���������
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Processing_Func.h"
#include <algorithm>
#include "Poison.h"	
#include "FirstProc.h"
#include "SecondProc.h"
#include "ThirdProc.h"
#include "FourthProc.h"
#include "FifthProc.h"
//#include "GLOBAL_CONST.h"
using namespace std;

Processing_Struct Processing_Func (Processing_Struct one, float lambda1, float lambda2, double dT)
{	bool first_que = true;

	// ��������� ������� �����
	while (first_que == true) 
	{
		// ���� ��� ��� ������� �����
		if (((one.a1.empty()) &&(one.a3.empty()))&& (one.a5.empty())) 	{ first_que = false;}
		else 
		{	
				// ���������� ����������� ������� W1 (������ �� ��� ����������)
				vector<long>::const_iterator lowest = min_element( one.W1.begin(), one.W1.end() );
				long bussy = *lowest;
				if (bussy > 0) {first_que = false;}

				else// ���� ��������� ����������
				{	// ������ � ����� ����� => �������� �� ������
					if ((one.a3.empty())&&(one.a5.empty()))
					{
						if (one.a1[0] < one.T_end)
						{
							one = FirstProc(one, lambda1);
												}
						else
						{
							first_que = false;
						}
					}
					else
					{
						// ����� ����� => �������� �� �������
						if (one.a5.empty())
						{
							one = ThirdProc(one, lambda1);
						}
						else
						{
							one = FifthProc(one, lambda1);
					
						}
					}
				}
			
		}
	}

	// ��������� ������� �����. 
	bool second_que = true;
	while (second_que == true)
	{
		if ((one.a2.empty()) &&(one.a4.empty())) 	{ second_que = false;}
		else 	
		{
			if (one.W2[0] == 0)
			{
				if (one.a4.empty()) 
				{
					one = SecondProc(one, lambda2);
				}
				else
				{
					one = FourthProc(one, lambda2);
					
				}
	
			}
			else {second_que = false;}
		}
	}

		one.T_start = one.T_end;
		one.T_end = one.T_end +dT;
	
		// ��������� W1.
		int size_block1 = one.W1.size();
		for (int i=0; i<size_block1; i++)
		{
			if (/*((one.T_start-dT)< one.Block_D1[i]) && */(one.Block_D1[i] <= one.T_end)) 
			{
				// ��������� �� ������ �������
				if (one.W1[i] == 1)	one.a2.push_back(one.Block_D1[i]);
				// ��������� � ��������� �������
				if (one.W1[i] == 3)	one.a4.push_back(one.Block_D1[i]);
				// ��������� � ������ �������
				if (one.W1[i] == 5)	one.a6.push_back(one.Block_D1[i]);
				// ���������� i-�� ������
				one.W1[i] = 0;
			}
		}


		// ������ ��� (������������������ ��������:
		// 1) �������� �������, 2)��������� ��������, 3)������ � ������� )
		// ��������� W2
		if (/*((one.T_start  - dT )< one.Block_D2[0]) &&*/ (one.Block_D2[0] <= one.T_end)) 
		{
			// ��������� � ������ �������
			if (one.W2[0] == 2)	one.a3.push_back(one.Block_D2[0]);
			// ��������� � ����� �������
			if (one.W2[0] == 4)	one.a5.push_back(one.Block_D2[0]);
			// ����������� ����
			one.W2[0] = 0;
		}


		return one;
}
