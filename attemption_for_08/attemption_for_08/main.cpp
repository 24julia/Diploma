#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "fRand.h"
#include "Poison.h"
#include "Kolmqvant.h"
#include "Processing_Func.h"
#include "FirstProc.h"
#include "New_struct.h"
#include "reduce_d1.h"
#include "increase_d1.h"
#include <fstream>
#include <time.h>
#include "GLOBAL_CONST.h"
#include "analysis1.h"

using namespace std;


	int main()
	{   srand( (unsigned)time( NULL ) );
		int i;
		//ОБЪЯВЛЕНИЕ ПЕРВОЙ ОЧЕРЕДИ И БЛОКОВ 
		vector<long> First_Signals1;
		vector<long> First_Signals2;
		/*// ВМЕСТО ДИНАМИЧЕСКОГО МАССИВА ВОЗЬМЕМ ВЕКТОР
		vector<long> Block_D1;
		vector<long> Block_D2;
		// Векторы занятости блоков D1 и D2
		vector<long> W1;
		vector<long> W2;

		// Заполнение векторов D1 и W1
		int n = 1;
		for (i=0; i<n; i++)
		{
			Block_D1.push_back(0);
			W1.push_back(0);
		}
		// Заполнение векторов D2  и W2
		Block_D2.push_back(0);
		W2.push_back(0);*/
//-----------------------------------------------------------------------
// ВЫЧИСЛЕНИЕ КОЛИЧЕСТВА ИТЕРАЦИЙ
		long N_itt;
		N_itt = Kolmqvant(insurance, sigma);
		
//ГЕНЕРАЦИЯ ЗАЯВОК ВО ВХОДНОМ ПОТОКЕ 
		long Exp_Random_V;
		for (i=0; i<N_itt; i++)
		{
			if (i==0) Exp_Random_V = -1*(1/lambda0)*log(fRand());
			else {Exp_Random_V = First_Signals1[i-1]-1*(1/lambda0)*log(fRand());}
			First_Signals1.push_back(Exp_Random_V);

			if (i==0) Exp_Random_V = -1*(1/lambda0)*log(fRand());
			else {Exp_Random_V = First_Signals2[i-1]-1*(1/lambda0)*log(fRand());}
			First_Signals2.push_back(Exp_Random_V);
		}

//ОСНОВНОЙ ЦИКЛ С ШАГОМ dT
		/*if (lambda2 > lambda1) 	{dT = lambda1/100;}
		else {dT = lambda2/100;}*/
		if (lambda2 < lambda1) 	{dT = lambda1*dT_koef;}
		else {dT = lambda2*dT_koef;}
		
		// определение главной структуры
	
		Processing_Struct MAIN_struct1 = New_struct(n,dT);
		Processing_Struct MAIN_struct2 = New_struct(n,dT);
		Processing_Struct MAIN_struct3 = New_struct(n,dT);
		Processing_Struct MAIN_struct4 = New_struct(n,dT);
		MAIN_struct1.a1 = First_Signals1;
		MAIN_struct2.a1 = First_Signals2;

		ofstream out;

        int n1 = 0;
		int n2 = 0;
		std::vector<int> analysis_res;
		analysis_res.push_back(n1);
		analysis_res.push_back(n2);
		int count1=MAIN_struct1.a6.size();
		int count4=MAIN_struct4.a6.size();
		long a6_last1 = 0, a6_last2 = 0, a6_last3 = 0;
		out.open("log.txt");
		//Основной цикл
		while (MAIN_struct4.a6.size() < 2*N_itt){
		if (n1 == 0 && n2 == 0){
			analysis_res = analysis1(MAIN_struct1, MAIN_struct2, MAIN_struct3, MAIN_struct4);
			n1 = analysis_res[0];
			n2 = analysis_res[1];
		}
		//Вынимаем сервер из узла n1
		if (n1 > 0){ switch (n1){
					case 1: {	MAIN_struct1.n = n1;
								MAIN_struct1 = reduce_d1(MAIN_struct1);
								n1 = MAIN_struct1.n;
								break;
					}
					case 2: {	MAIN_struct2.n = n1;
								MAIN_struct2 = reduce_d1(MAIN_struct2);
								n1 = MAIN_struct2.n;
								break;
					}
					case 3: {	MAIN_struct3.n = n1;
								MAIN_struct3 = reduce_d1(MAIN_struct3);
								n1 = MAIN_struct3.n;
								break;
					}
					case 4: {	MAIN_struct4.n = n1;
								MAIN_struct4 = reduce_d1(MAIN_struct4);
								n1 = MAIN_struct4.n;
								break;
					}

				}
		}
		//Запихиваем сервер в узел n2
		if (n1 = 0) { switch (n2){
					case 1: {	MAIN_struct1 = increase_d1(MAIN_struct1);
								break;
					}
					case 2: {	MAIN_struct2 = increase_d1(MAIN_struct2);
								break;
							}
					case 3: {	MAIN_struct3 = increase_d1(MAIN_struct3);
								break;
							}
					case 4: {	MAIN_struct4 = increase_d1(MAIN_struct4);
								break;
							}

					}
					n2 = 0;
		}
			
			//Функция обработки
			//4 блок
			MAIN_struct4 = Processing_Func (MAIN_struct4);
			//3 блок
			if (!MAIN_struct3.a6.empty()) 
				a6_last1 = MAIN_struct3.a6.back();

			MAIN_struct3 = Processing_Func (MAIN_struct3);

			if (!MAIN_struct3.a6.empty() && (a6_last3 != MAIN_struct3.a6.back()))
				MAIN_struct4.a1.push_back(MAIN_struct3.a6.back());
			//2 блок
			if (!MAIN_struct2.a6.empty()) 
				a6_last1 = MAIN_struct2.a6.back();

			MAIN_struct2 = Processing_Func (MAIN_struct2);

			if (!MAIN_struct2.a6.empty() && (a6_last2 != MAIN_struct2.a6.back()))
				MAIN_struct3.a1.push_back(MAIN_struct2.a6.back());
			//1 блок
			if (!MAIN_struct1.a6.empty()) 
				a6_last1 = MAIN_struct1.a6.back();

			MAIN_struct1 = Processing_Func (MAIN_struct1);
			if ((!MAIN_struct1.a6.empty()) && (a6_last1 != MAIN_struct1.a6.back()))
				MAIN_struct3.a1.push_back(MAIN_struct1.a6.back());	

			// LOG
			
					if (count1!=MAIN_struct1.a6.size()){
						cout << MAIN_struct1.a6.size() << " of_1 " << N_itt<< " D1: "  << MAIN_struct1.Block_D1[0]<< " D2: " <<MAIN_struct1.Block_D2[0]<< " T_end: " <<MAIN_struct1.T_end<< endl;
						out << MAIN_struct1.a6.size() << " of_1 " << N_itt<< " D1: "  << MAIN_struct1.Block_D1[0]<< " D2: " <<MAIN_struct1.Block_D2[0]<< " T_end: " <<MAIN_struct1.T_end<< endl;
						count1=MAIN_struct1.a6.size();
					}
					if (count4!=MAIN_struct4.a6.size()){
						cout << MAIN_struct4.a6.size() << " of_4 " << N_itt<< " D1: "  << MAIN_struct4.Block_D1[0]<< " D2: " <<MAIN_struct4.Block_D2[0]<< " T_end: " <<MAIN_struct4.T_end<< endl;
						out << MAIN_struct4.a6.size() << " of_4 " << N_itt<< " D1: "  << MAIN_struct4.Block_D1[0]<< " D2: " <<MAIN_struct4.Block_D2[0]<< " T_end: " <<MAIN_struct4.T_end<< endl;
						count4=MAIN_struct4.a6.size();
					}

		}	out.close();	

		//запись в файл

        out.open("file.txt");
		for (i=0; i<MAIN_struct1.a6.size(); i++){
			out<<MAIN_struct1.a6[i]<<endl;
		}
		out.close();

		out.open("Time_in_1_block.txt");
		for (i=0; i<N_itt; i++){
			out<<MAIN_struct1.a6[i]-First_Signals1[i]<<endl;
		}
		out.close();
		
		return 0;
	}
