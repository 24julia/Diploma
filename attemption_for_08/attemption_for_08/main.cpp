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
		//���������� ������ ������� � ������ 
		vector<long> First_Signals1;
		vector<long> First_Signals2;
//-----------------------------------------------------------------------
// ���������� ���������� ��������
		long N_itt;
		N_itt = Kolmqvant(insurance, sigma);
		
//��������� ������ �� ������� ������ 
		long Exp_Random_V;
		for (i=0; i<N_itt/(2*koef_unlock)+1; i++)
		{
			if (i==0) Exp_Random_V = -1*(1/lambda0)*log(fRand());
			else {Exp_Random_V = First_Signals1[i-1]-1*(1/lambda0)*log(fRand());}
			First_Signals1.push_back(Exp_Random_V);

			if (i==0) Exp_Random_V = -1*(1/lambda0)*log(fRand());
			else {Exp_Random_V = First_Signals2[i-1]-1*(1/lambda0)*log(fRand());}
			First_Signals2.push_back(Exp_Random_V);
		}

//�������� ���� � ����� dT
		/*if (lambda2 > lambda1) 	{dT = lambda1/100;}
		else {dT = lambda2/100;}*/
		if (lambda2 < lambda1) 	{dT = lambda1*dT_koef;}
		else {dT = lambda2*dT_koef;}
		
		// ����������� ������� ���������
		Processing_Struct State_of_all[4];
		for (i=0; i<4; i++) State_of_all[i] = New_struct(n,dT);		
		State_of_all[0].a1 = First_Signals1;
		State_of_all[1].a1 = First_Signals2;

		ofstream out;

        int n1 = -1;
		int n2 = -1;
		int* analysis_res = new int[2];
		analysis_res[0] = n1;
		analysis_res[1] = n2;
		int count[4];
		for (i=0; i<4; i++) count[i]=State_of_all[i].a6.size();
		std::vector<long> a1[4];
		out.open("log.txt");
		//�������� ����
		while (a1[3].size() < N_itt){
			if (n1 == -1 && n2 == -1){
				analysis_res = analysis1(State_of_all);
				n1 = analysis_res[0];
				n2 = analysis_res[1];
				if(n1!=-1 && n2!=-1){
				cout<<n1+1<<"(" << State_of_all[n1].Block_D1.size()<<") "<<n2+1<<"(" << State_of_all[n2].Block_D1.size()<<") "<<endl;
				 out<<n1+1<<"(" << State_of_all[n1].Block_D1.size()<<") "<<n2+1<<"(" << State_of_all[n2].Block_D1.size()<<") "<<endl;
				}
			}
			//�������� ������ �� ���� n1
			if (n1 >= 0){ 
				State_of_all[n1].n = n1;
				State_of_all[n1] = reduce_d1(State_of_all[n1]);
				n1 = State_of_all[n1].n;
			}			
			//���������� ������ � ���� n2
			if ((n1 == -1)&&(n2 >= 0)) { 
				State_of_all[n2] = increase_d1(State_of_all[n2]);
				n2 = -1;
			}
			
			//������� ���������
			//4 ����
			State_of_all[3] = Processing_Func (State_of_all[3]);
			while (!State_of_all[3].a6.empty()){
					a1[3].push_back(State_of_all[3].a6.front());
					State_of_all[3].a6.erase(State_of_all[3].a6.begin());
				}
			//3-1 ����
			for(i=2;i>=0;i--){
				State_of_all[i] = Processing_Func (State_of_all[i]);
				while (!State_of_all[i].a6.empty()){
					
					if (i==0){
						State_of_all[2].a1.push_back(State_of_all[0].a6.front());
					}else{
						if (i==1){
							State_of_all[2].a1.push_back(State_of_all[1].a6.front());
						}else{
							if(a1[3].size()<(koef_unlock+0.1)*a1[2].size()){
								State_of_all[3].a1.push_back(State_of_all[2].a6.front());
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
					cout << a1[i].size() << "/"<<(N_itt/(2*koef_unlock)+1)<<" out of " << i+1 << "(" << State_of_all[i].Block_D1.size()<<") "<< n1 <<" "<< n2 << " D1: "  << State_of_all[i].Block_D1[0]<< " D2: " <<State_of_all[i].Block_D2[0]<< " T_end: " <<State_of_all[i].T_end<< endl;
					 out << a1[i].size() << "/"<<(N_itt/(2*koef_unlock)+1)<<" out of " << i+1 << "(" << State_of_all[i].Block_D1.size()<<") "<< n1 <<" "<< n2 << " D1: "  << State_of_all[i].Block_D1[0]<< " D2: " <<State_of_all[i].Block_D2[0]<< " T_end: " <<State_of_all[i].T_end<< endl;
					count[i]=a1[i].size();
				}
			}
					
		}	
	
		return 0;
	}
