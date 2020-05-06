#include <iostream>
#include <vector>
#include "EllipticCurve.h"

void output(EllipticCurve curve) {
	cout << "Таблица, сгенерированная сложением точек в афинных координатах" << endl;
	curve.outputTable();

	vector<PointOnCurve> vec = curve.generateAllPoints();
	cout << endl << "Порядки точек кривой" << endl;
	for (auto x : vec)
		cout << " = " << curve.findOrderOfPoint(x) << endl;

	cout << endl << "Таблица, сгенерированная сложением точек в проективных координатах" << endl;
	curve.outputTableProective();
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");

	M_LONG a = { 1,1 };
	M_LONG b = { 1,0xB };
	EllipticCurve curve(4, 1, a, b);

	cout << "Для подготовленных данных" << endl;
	output(curve);

	M_LONG a1 = { 1,4 }; // 15 вариант
	M_LONG b1 = { 1,9 };  // 15 вариант
	EllipticCurve curve1(4, 1, a1, b1);

	cout << endl << "Для варианта №15" << endl;
	output(curve1);

	system("pause");
	return 0;
}