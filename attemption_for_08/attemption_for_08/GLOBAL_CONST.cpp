#include "GLOBAL_CONST.h"

double dT;
	
//���������� �������� (����� ������� �� ���� ������ �� ������)
//0.005 = 200 0.01 = 100 0.025=40
const double lambda0 = 0.005; // ���������� ����������������� ������������� 
const double lambda1 = 0.025; // �������� ���������� ������������� ������������� ��� ����� D1
const double lambda2 = 0.025; // �������� ���������� �������������� ������������ ��� ����� D2
const  int n=1000; // ����� ������ � D1
const double dT_koef = 500;
extern const float koef_unlock = 0.2;

// ������ �� �������
const double sigma=0.03; // ���������� ����������� 
const double insurance = 0.95; // ������� �������������