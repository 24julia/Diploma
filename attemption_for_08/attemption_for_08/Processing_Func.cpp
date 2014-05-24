// функци€ обработки
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

	// обработка первого блока
	while (first_que == true) 
	{
		// если все три очереди пусты
		if (((one.a1.empty()) &&(one.a3.empty()))&& (one.a5.empty())) 	{ first_que = false;}
		else 
		{	
				// определ€ем минимальный элемент W1 (зан€ты ли все устройства)
				vector<long>::const_iterator lowest = min_element( one.W1.begin(), one.W1.end() );
				long bussy = *lowest;
				if (bussy > 0) {first_que = false;}

				else// есть свободное устройство
				{	// треть€ и п€та€ пусты => выбираем из первой
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
						// п€та€ пуста => выбираем из третьей
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

	// обработка второго блока. 
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
	
		// изменение W1.
		int size_block1 = one.W1.size();
		for (int i=0; i<size_block1; i++)
		{
			if (/*((one.T_start-dT)< one.Block_D1[i]) && */(one.Block_D1[i] <= one.T_end)) 
			{
				// добавл€ем во вторую очередь
				if (one.W1[i] == 1)	one.a2.push_back(one.Block_D1[i]);
				// добавл€ем в четвертую очередь
				if (one.W1[i] == 3)	one.a4.push_back(one.Block_D1[i]);
				// добавл€ем в шестую очередь
				if (one.W1[i] == 5)	one.a6.push_back(one.Block_D1[i]);
				// освобожаем i-ую €чейку
				one.W1[i] = 0;
			}
		}


		//  ќ—я ј Ќ≈“ (последовательность действий:
		// 1) изменени времени, 2)изменение очередей, 3)работа с блоками )
		// изменение W2
		if (/*((one.T_start  - dT )< one.Block_D2[0]) &&*/ (one.Block_D2[0] <= one.T_end)) 
		{
			// добавл€ем в третью очередь
			if (one.W2[0] == 2)	one.a3.push_back(one.Block_D2[0]);
			// добавл€ем в п€тую очередь
			if (one.W2[0] == 4)	one.a5.push_back(one.Block_D2[0]);
			// освобождаем узел
			one.W2[0] = 0;
		}


		return one;
}
