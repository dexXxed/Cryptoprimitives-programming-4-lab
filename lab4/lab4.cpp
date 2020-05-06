#include <iostream>
#include <vector>
#include "EllipticCurve.h"

void output(EllipticCurve curve) {
	cout << "�������, ��������������� ��������� ����� � ������� �����������" << endl;
	curve.outputTable();

	vector<PointOnCurve> vec = curve.generateAllPoints();
	cout << endl << "������� ����� ������" << endl;
	for (auto x : vec)
		cout << " = " << curve.findOrderOfPoint(x) << endl;

	cout << endl << "�������, ��������������� ��������� ����� � ����������� �����������" << endl;
	curve.outputTableProective();
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");

	M_LONG a = { 1,1 };
	M_LONG b = { 1,0xB };
	EllipticCurve curve(4, 1, a, b);

	cout << "��� �������������� ������" << endl;
	output(curve);

	M_LONG a1 = { 1,4 }; // 15 �������
	M_LONG b1 = { 1,9 };  // 15 �������
	EllipticCurve curve1(4, 1, a1, b1);

	cout << endl << "��� �������� �15" << endl;
	output(curve1);

	system("pause");
	return 0;
}