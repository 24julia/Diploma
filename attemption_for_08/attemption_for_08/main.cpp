#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
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
//#include "GLOBAL_CONST.h"
#include "analysis1.h"

using namespace std;


int main()
	{   srand( (unsigned)time( NULL ) );
		int i;
		//0.005 = 200 0.01 = 100 0.025=40	0.075 = 3/40
		double dT = 1;
		float lambda0 = 0.05; // показатель экспоненциального распределения 
		float lambda2 = 0.025*2; // задается показатель пуассоновского распрделения для блока D2
		float lambda1 = lambda2*3/2/8;  // задается показатель пуассновского распределения для блока D1
		int n=4000; // число блоков в D1
		double dT_koef = 500;
		float koef_unlock = 0.005;
		long sum;

		float sigma=0.03; // допустимая погрешность 
		float insurance = 0.95; // степень неуверенности
		
// ВЫЧИСЛЕНИЕ КОЛИЧЕСТВА ИТЕРАЦИЙ
		long N_itt;
		N_itt = Kolmqvant(insurance, sigma);
		
		long Exp_Random_V;
		ofstream out;
		ofstream out2;
		out.open("log.txt");
//цикл по нагрузке
		for(int file_i=1; file_i<=20; file_i++){
			float lambda0 = 0.005*file_i;
			std::string file_name = "stat" + std::to_string(static_cast<long long>(file_i)) + ".txt";
			out2.open(file_name);
			int j;
//цикл по количеству узлов
			for (j=1; j<=20; j ++){
				n=j;
				float lambda1 = lambda0*3/j;
				vector<long> First_Signals1;
				vector<long> First_Signals2;
				for (i=0; i<N_itt; i++){	
					if (i==0) Exp_Random_V = -1*(1/lambda0)*log(fRand());
					else {Exp_Random_V = First_Signals1[i-1]-1*(1/lambda0)*log(fRand());}
					First_Signals1.push_back(Exp_Random_V);
				}
				for(i=0; i<N_itt/100;i++){
					if (i==0) Exp_Random_V = -1*(1/500*lambda0)*log(fRand());
					else {Exp_Random_V = First_Signals2[i-1]-1*(1/500*lambda0)*log(fRand());}
					First_Signals2.push_back(Exp_Random_V);
				}
		
		// определение главной структуры
				Processing_Struct State_of_all[4];
				for (i=0; i<4; i++) State_of_all[i] = New_struct(n,dT);		
				State_of_all[0].a1 = First_Signals1;
				State_of_all[1].a1 = First_Signals2;

				int n1 = -1;
				int n2 = -1;
				int* analysis_res = new int[2];
				analysis_res[0] = n1;
				analysis_res[1] = n2;
				int count[4];
				for (i=0; i<4; i++) count[i]=State_of_all[i].a6.size();
				std::vector<long> a1[5];
				int que_len = 0;
		//Основной цикл				
				while (a1[3].size() < N_itt*koef_unlock){
					if (n1 == -1 && n2 == -1){
						//analysis_res = analysis1(State_of_all);
						//n1 = analysis_res[0];
						//n2 = analysis_res[1];
						if(n1!=-1 && n2!=-1){
							//cout<<n1+1<<"(" << State_of_all[n1].Block_D1.size()<<") "<<n2+1<<"(" << State_of_all[n2].Block_D1.size()<<") "<<endl;
							//out<<n1+1<<"(" << State_of_all[n1].Block_D1.size()<<") "<<n2+1<<"(" << State_of_all[n2].Block_D1.size()<<") "<<endl;
						}
					}
			//Вынимаем сервер из узла n1
					if (n1 >= 0){ 
						State_of_all[n1].n = n1;
						State_of_all[n1] = reduce_d1(State_of_all[n1]);
						n1 = State_of_all[n1].n;
					}			
			//Запихиваем сервер в узел n2
					if ((n1 == -1)&&(n2 >= 0)) { 
						State_of_all[n2] = increase_d1(State_of_all[n2]);
						n2 = -1;
					}			
				//Функция обработки
				//4 блок
					State_of_all[3] = Processing_Func (State_of_all[3], lambda1, lambda2, dT);
					while (!State_of_all[3].a6.empty()){
						a1[3].push_back(State_of_all[3].a6.front());
						State_of_all[3].a6.erase(State_of_all[3].a6.begin());
					}
					//3-1 блок ЗДЕСЬ ИЗМЕНЁН ЦИКЛ ДОЛЖНО БЫТЬ I=2
					for(i=2;i>=0;i--){
						State_of_all[i] = Processing_Func (State_of_all[i], lambda1, lambda2, dT);
						while (!State_of_all[i].a6.empty()){					
							if (i==0){
								State_of_all[2].a1.push_back(State_of_all[0].a6.front());
							}else{
								if (i==1){
									State_of_all[2].a1.push_back(State_of_all[1].a6.front());
								}else{
									if(a1[3].size()<(koef_unlock*1.05)*a1[2].size()){
										State_of_all[3].a1.push_back(State_of_all[2].a6.front());
										a1[4].push_back(State_of_all[i].a6.front());
									}
								}
							}
						a1[i].push_back(State_of_all[i].a6.front());
						State_of_all[i].a6.erase(State_of_all[i].a6.begin());
						}
					}
			// LOG
					for (i=0;i<4;i++){
						if (count[i]!=a1[i].size()){
							cout << a1[i].size() << "/"<<(N_itt)<<" out of " << i+1 << "(" << State_of_all[i].Block_D1.size()<<") "<< n1 <<" "<< n2 << " D1: "  << State_of_all[i].Block_D1[0]<< " D2: " <<State_of_all[i].Block_D2[0]<< " T_end: " <<State_of_all[i].T_end<< endl;
							// out << a1[i].size() << "/"<<(N_itt/(2*koef_unlock)+1)<<" out of " << i+1 << "(" << State_of_all[i].Block_D1.size()<<") "<< n1 <<" "<< n2 << " D1: "  << State_of_all[i].Block_D1[0]<< " D2: " <<State_of_all[i].Block_D2[0]<< " T_end: " <<State_of_all[i].T_end<< endl;
							count[i]=a1[i].size();
						}
					}
					if 	(a1[0].size() == N_itt/2){
						que_len = queue_len(State_of_all[0], 1);
					}
				}
				out2<<j<<endl;
				int cdr;
				int in_3;
				int in;
				bool find;
				std::vector<long>  from1and2(a1[0].size()+a1[1].size());
				std::sort (a1[0].begin(), a1[0].end()); 
				std::sort (a1[1].begin(), a1[1].end()); 
				merge(a1[0].begin(), a1[0].end(), a1[1].begin(), a1[1].end(), from1and2.begin()) ;
				for (cdr=0; cdr<a1[3].size(); cdr++){//для каждой вышедшей из 4
					find = false;
					for (in_3=0; in_3<a1[2].size(); in_3++){// подбираем номер в полном списке вышедших из 3
						if (find) break;
						if (a1[2][in_3] == a1[4][cdr]){//если подобрали
							for (in=0; in<a1[1].size(); in++){//ищем в списке вышедших из 2
								if ((find==false)&&(a1[1][in] == from1and2[in_3])){
									out2<<" "<<a1[3][cdr] -First_Signals2[in];
									find = true;
								}
							}
							for (in=0; in<a1[0].size(); in++){//ищем в списке вышедших из 1
								if ((find==false)&&(a1[0][in] == from1and2[in_3])){
									out2<<" "<<a1[3][cdr] -First_Signals1[in];
									find = true;
								}
							}
						}
					}
				}
				out2<<endl;

				find = false;
				for (in_3=0; in_3<a1[2].size(); in_3++){//для каждой вышедшей из 3
					find = false;
					for (in=0; in<a1[1].size(); in++){//ищем в списке вышедших из 2
						if (find) break;
						if (a1[1][in] == from1and2[in_3]){
							out2<<" "<<a1[2][in_3] - First_Signals2[in];
							find = true;
						}
					}
					for (in=0; in<a1[0].size(); in++){//ищем в списке вышедших из 1
						if (find) break;
						if (a1[0][in] == from1and2[in_3]){
							out2<<" "<<a1[2][in_3] - First_Signals1[in];
							find = true;
						}
					}
				}
				out2<<endl;
			}
//цикл по количеству узлов
			out2.close();
		}
//цикл по нагрузке
		return 0;
	}
