#include "EllipticCurve.h"

EllipticCurve::EllipticCurve(unsigned int m, unsigned int k1, unsigned int k2, unsigned int k3, M_LONG _a, M_LONG _b) {
	if (m <= k1 || k1 == 0)
		throw std::invalid_argument("");

	if (k2 == 0)
		if (k3 != 0)
			throw std::invalid_argument("");

	else if (k1 <= k2 || k2 <= k3)
		throw std::invalid_argument("");

	setBits(polynom, { m, k1, k2, k3, 0 });
	m_copy(a, _a);
	m_copy(b, _b);
}

EllipticCurve::EllipticCurve(unsigned int m, unsigned int k, M_LONG _a, M_LONG _b) {
	if (m <= k || k == 0)
		throw std::invalid_argument("");

	setBits(polynom, { m,k,0 });
	m_copy(a, _a);
	m_copy(b, _b);
}

bool EllipticCurve::isPointOnCurve(PointOnCurve point) {
	M_LONG first;
	M_LONG tmp1, tmp2;
	sqrmod_pol(point.y, polynom, tmp1);
	mulmod_pol(point.x, point.y, polynom, tmp2);
	add_pol(tmp1, tmp2, first);

	M_LONG second;
	sqrmod_pol(point.x, polynom, tmp1);
	mulmod_pol(point.x, tmp1, polynom, second);

	mulmod_pol(a, tmp1, polynom, tmp2);

	add_pol(second, tmp2, second);
	add_pol(second, b, second);

	return !m_cmp(first, second);
}

vector<PointOnCurve> EllipticCurve::generateAllPoints() {
	vector<PointOnCurve> result;
	int m = degree(polynom);
	M_LONG x = { 1,0 };
	M_LONG y = { 1,0 };
	PointOnCurve point(x, y);

	for (; degree(point.x) < m; incrM_LONG(point.x))
		for (point.y[0] = 1, point.y[1] = 0; degree(point.y) < m; incrM_LONG(point.y))
			if (isPointOnCurve(point))
				result.push_back(point);

	return result;
}

vector<vector<PointOnCurve>> EllipticCurve::buildTable() {
	vector<PointOnCurve > points = generateAllPoints();

	vector<vector<PointOnCurve>> table;
	int numberOfPoints = points.size();
	table.resize(numberOfPoints + 1);

	for (int i = 0; i < numberOfPoints + 1; i++)
		table[i].resize(numberOfPoints + 1);

	table[0][0] = points[0];

	for (int i = 0; i < numberOfPoints; i++) {
		table[0][i + 1] = points[i];
		table[i + 1][0] = points[i];
	}

	for (int i = 1; i < numberOfPoints + 1; i++)
		for (int j = i + 1; j < numberOfPoints + 1; j++) {
			addTwoPoints(table[i][0], table[0][j], table[i][j]);
			table[j][i] = table[i][j];
		}

	for (int i = 1; i < numberOfPoints + 1; i++)
		addTwoPoints(table[i][0], table[0][i], table[i][i]);

	return table;
}

void EllipticCurve::outputTable() {
	vector<vector<PointOnCurve>> table = buildTable();
	cout << "|     ";
	int j = 1;
	int size = table.size();

	for (int i = 0; i < size; i++) {
		cout << '|';
		for (; j < size; j++)
			cout << table[i][j] << '|';
		cout << endl;
		j = 0;
	}
}

void EllipticCurve::addTwoPoints(PointInProectiveCoordinats &a, PointInProectiveCoordinats &b, PointInProectiveCoordinats &result) {
	if (!isPointOnCurve(a) || !isPointOnCurve(b))
		throw std::invalid_argument("Point doesn`t belong to curve");

	if (a == b)
		doublePoint(a, result);
	else
		addPoints(a, b, result);
}

int EllipticCurve::findOrderOfPoint(PointOnCurve &a) {
	PointOnCurve point1 = a, 
		         point2;
	PointOnCurve *pointer1 = &point1, 
		         *pointer2 = &point2;
	int i = 0;

	while (!pointer1->isInfinityPoint()) {
		if (i)
			cout << "->";

		cout << *pointer1;
		i++;
		addTwoPoints(*pointer1, a, *pointer2);
		std::swap(pointer1, pointer2);
	}

	return ++i;
}

bool EllipticCurve::isPointOnCurve(PointInProectiveCoordinats &point) {
	M_LONG first;
	M_LONG tmp1, tmp2;

	sqrmod_pol(point.y, polynom, first);
	mulmod_pol(point.x, point.y, polynom, tmp1);
	mulmod_pol(tmp1, point.z, polynom, tmp2);
	add_pol(first, tmp2, first);

	M_LONG second;
	sqrmod_pol(point.x, polynom, tmp1);
	mulmod_pol(tmp1, point.x, polynom, tmp2);
	mulmod_pol(tmp2, point.z, polynom, second);

	mulmod_pol(point.x, point.z, polynom, tmp1);
	sqrmod_pol(tmp1, polynom, tmp2);
	mulmod_pol(tmp2, a, polynom, tmp1);
	add_pol(second, tmp1, second);

	sqrmod_pol(point.z, polynom, tmp1);
	sqrmod_pol(tmp1, polynom, tmp2);
	mulmod_pol(tmp2, b, polynom, tmp1);
	add_pol(second, tmp1, second);

	return !m_cmp(first, second);
}

PointOnCurve EllipticCurve::proectiveToAffin(PointInProectiveCoordinats &point) {
	PointOnCurve result;
	if (point.isInfinityPoint()) {
		result.x[0] = result.y[0] = 1;
		result.x[1] = result.y[1] = 0;
	} else {
		M_LONG tmp1, tmp2;
		inv_pol(point.z, polynom, tmp1);
		mulmod_pol(point.x, tmp1, polynom, result.x);

		sqrmod_pol(tmp1, polynom, tmp2);
		mulmod_pol(point.y, tmp2, polynom, result.y);
	}

	return result;
}

vector<PointInProectiveCoordinats> EllipticCurve::generateAllPointsProective() {
	vector<PointInProectiveCoordinats> result;
	int m = degree(polynom);
	M_LONG x = { 1,0 };
	M_LONG y = { 1,0 };
	M_LONG z = { 1,1 };
	PointInProectiveCoordinats point(x, y, z);

	for (; degree(point.x) < m; incrM_LONG(point.x))
		for (point.y[0] = 1, point.y[1] = 0; degree(point.y) < m; incrM_LONG(point.y))
			if (isPointOnCurve(point) && isPointOnCurve(proectiveToAffin(point)))
					result.push_back(point);

	return result;
}

vector<vector<PointInProectiveCoordinats>> EllipticCurve::buildTableProective() {
	vector<PointInProectiveCoordinats> points = generateAllPointsProective();

	vector<vector<PointInProectiveCoordinats>> table;
	int numberOfPoints = points.size();
	table.resize(numberOfPoints + 1);

	for (int i = 0; i < numberOfPoints + 1; i++)
		table[i].resize(numberOfPoints + 1);

	table[0][0] = points[0];

	for (int i = 0; i < numberOfPoints; i++) {
		table[0][i + 1] = points[i];
		table[i + 1][0] = points[i];
	}

	for (int i = 1; i < numberOfPoints + 1; i++)
		for (int j = i + 1; j < numberOfPoints + 1; j++) {
			addTwoPoints(table[i][0], table[0][j], table[i][j]);
			table[j][i] = table[i][j];
		}

	for (int i = 1; i < numberOfPoints + 1; i++)
		addTwoPoints(table[i][0], table[0][i], table[i][i]);

	return table;
}

void EllipticCurve::incrM_LONG(M_LONG a) {
	a[1]++;

	for (int i = 1; i < a[0] && a[i] == 0; i++)
		a[i + 1]++;

	if (a[a[0]] == 0) {
		a[0]++;
		a[a[0]] = 1;
	}
}

void EllipticCurve::outputTableProective() {
	vector<vector<PointInProectiveCoordinats>> table = buildTableProective();
	cout << "|     ";
	int j = 1;
	int size = table.size();

	for (int i = 0; i < size; i++) {
		cout << '|';

		for (; j < size; j++)
			cout << proectiveToAffin( table[i][j]) << '|';
		
		cout << endl;
		j = 0;
	}
}

void EllipticCurve::doublePoint(PointInProectiveCoordinats &point, PointInProectiveCoordinats  &result) {
	M_LONG tmp1, tmp2;

	mulmod_pol(point.x, point.z, polynom, tmp1);
	sqrmod_pol(tmp1, polynom, result.z);

	M_LONG bZ4;
	sqrmod_pol(point.z, polynom, bZ4);
	sqrmod_pol(bZ4, polynom, tmp1);
	mulmod_pol(tmp1, b, polynom, bZ4);

	sqrmod_pol(point.x, polynom, tmp1);
	sqrmod_pol(tmp1, polynom, result.x);
	add_pol(result.x, bZ4, result.x);

	mulmod_pol(result.z, bZ4, polynom, result.y);
	mulmod_pol(result.z, a, polynom, tmp1);
	add_pol(tmp1, bZ4, tmp1);
	sqrmod_pol(point.y, polynom, tmp2);
	add_pol(tmp1, tmp2, tmp1);
	mulmod_pol(tmp1, result.x, polynom, tmp2);
	add_pol(result.y, tmp2, result.y);
}

void EllipticCurve::addPoints(PointInProectiveCoordinats &first, PointInProectiveCoordinats &second, PointInProectiveCoordinats  &result) {
	if (second.z[0] != 1 || second.z[1] != 1) {
		cout << "Ошибка, вторая точка должна быть (x, y, 1)" << endl;
		return;
	}

	M_LONG tmp1, tmp2;
	mulmod_pol(first.z, second.x, polynom, tmp1);

	if (!m_cmp(tmp1, first.x)) {
		sqrmod_pol(first.z, polynom, tmp1);
		mulmod_pol(tmp1, second.y, polynom, tmp2);

		if (!m_cmp(tmp2, first.y)) {
			doublePoint(first, result);
			return;
		}
	}

	M_LONG A, B, C, D, E, F, G, tmp;
	sqrmod_pol(first.z, polynom, tmp);
	mulmod_pol(tmp, second.y, polynom, A);
	add_pol(A, first.y, A);

	mulmod_pol(second.x, first.z, polynom, B);
	add_pol(B, first.x, B);

	mulmod_pol(first.z, B, polynom, C);

	sqrmod_pol(first.z, polynom, tmp);
	mulmod_pol(tmp, a, polynom, D);
	add_pol(D, C, E);
	sqrmod_pol(B, polynom, tmp);
	mulmod_pol(E, tmp, polynom, D);

	sqrmod_pol(C, polynom, result.z);

	mulmod_pol(A, C, polynom, E);

	sqrmod_pol(A, polynom, result.x);
	add_pol(result.x, D, result.x);
	add_pol(result.x, E, result.x);

	mulmod_pol(second.x, result.z, polynom, F);
	add_pol(F, result.x, F);

	mulmod_pol(second.y, result.z, polynom, G);
	add_pol(G, result.x, G);

	mulmod_pol(E, F, polynom, tmp);
	mulmod_pol(G, result.z, polynom, result.y);
	add_pol(result.y, tmp, result.y);
}

void  EllipticCurve::addTwoPoints(PointOnCurve &first, PointOnCurve &second, PointOnCurve &result) {
	if (!isPointOnCurve(first) || !isPointOnCurve(second))
		throw std::invalid_argument("Точка не пренадлежит кривой!");

	if (first.isInfinityPoint()) {
		result = second;
		return;
	}

	if (second.isInfinityPoint()) {
		result = first;
		return;
	}

	M_LONG r, tmp;
	if (!m_cmp(first.x, second.x)) {

		if (m_cmp(first.y, second.y) || (first.x[0] == 1 && first.x[1] == 0)) {
			result.x[0] = 1; result.x[1] = 0;
			result.y[0] = 1; result.y[1] = 0;
			return;
		}

		inv_pol(first.x, polynom, tmp);
		mulmod_pol(tmp, first.y, polynom, r);
		add_pol(r, first.x, r);

		sqrmod_pol(r, polynom, result.x);
		add_pol(result.x, r, result.x);
		add_pol(result.x, a, result.x);
	} else {
		M_LONG X, Y;

		add_pol(first.x, second.x, X);
		add_pol(first.y, second.y, Y);
		inv_pol(X, polynom, tmp);
		mulmod_pol(tmp, Y, polynom, r);

		sqrmod_pol(r, polynom, result.x);
		add_pol(result.x, r, result.x);
		add_pol(result.x, first.x, result.x);
		add_pol(result.x, second.x, result.x);
		add_pol(result.x, a, result.x);
	}

	add_pol(result.x, first.x, tmp);
	mulmod_pol(tmp, r, polynom, result.y);
	add_pol(result.y, result.x, result.y);
	add_pol(result.y, first.y, result.y);
}