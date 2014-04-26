#ifndef _PROCESSINGFUNC_
#define _PROCESSINGFUNC_
//#include <vector>
struct Processing_Struct {
long T_start;
long T_end;
//int n; // кол-во блоков в узле номер 1
std::vector<long> a1;
std::vector<long> a2;
std::vector<long> a3;
std::vector<long> a4;
std::vector<long> a5;
std::vector<long> a6;
std::vector<long> Block_D1;
std::vector<long> Block_D2;
std::vector<long> W1; // =1 если значени из очереди 1. =3 ...
std::vector<long> W2;
long n;//0-успешно изъят элемент
};

Processing_Struct Processing_Func(Processing_Struct);
 
#endif