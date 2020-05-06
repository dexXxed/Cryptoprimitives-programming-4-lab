#pragma once

#include <vector>
#include "MMATH.H"
#include "PolynomsLib_Bin_1.H"
#include "PointOnCurve.h"
#include "PointInProectiveCoordinats.h"

using std::vector;


struct EllipticCurve
{
	M_LONG polynom;
	M_LONG a, b;

	EllipticCurve(unsigned int m, unsigned int k1, unsigned int k2, unsigned int k3, M_LONG _a, M_LONG _b);

	EllipticCurve(unsigned int m, unsigned int k, M_LONG _a, M_LONG _b);

	bool isPointOnCurve(PointOnCurve point);

	vector<PointOnCurve> generateAllPoints();

	vector<vector<PointOnCurve>> buildTable();

	void outputTable();

	void addTwoPoints(PointOnCurve &a, PointOnCurve &b, PointOnCurve &result);

	void addTwoPoints(PointInProectiveCoordinats &a, PointInProectiveCoordinats &b, PointInProectiveCoordinats &result);

	int findOrderOfPoint(PointOnCurve &a);

	bool isPointOnCurve(PointInProectiveCoordinats &point);

	PointOnCurve proectiveToAffin(PointInProectiveCoordinats &point);

	vector<PointInProectiveCoordinats> generateAllPointsProective();

	vector<vector<PointInProectiveCoordinats>> buildTableProective();

	void outputTableProective();

private:
	void incrM_LONG(M_LONG a);

	void doublePoint(PointInProectiveCoordinats &point, PointInProectiveCoordinats  &result);

	void addPoints(PointInProectiveCoordinats &first, PointInProectiveCoordinats &second, PointInProectiveCoordinats  &result);
};

