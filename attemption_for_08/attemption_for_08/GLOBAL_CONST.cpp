#include "GLOBAL_CONST.h"

double dT;
	
//ОБЪЯВЛЕНИЕ КОНСТАНТ (ПОЗЖЕ ЗАМЕНИМ НА ВВОД ДАННЫХ ИЗ ОКОШКА)
//0.005 = 200 0.01 = 100 0.025=40
const double lambda0 = 0.005; // показатель экспоненциального распределения 
const double lambda1 = 0.025; // задается показатель пуассновского распределения для блока D1
const double lambda2 = 0.025; // задается показатель пуассоновского распрделения для блока D2
const  int n=1000; // число блоков в D1
const double dT_koef = 500;
extern const float koef_unlock = 1;

// ВООБЩЕ НЕ ТРОГАЕМ
const double sigma=0.1; // допустимая погрешность 
const double insurance = 0.95; // степень неуверенности