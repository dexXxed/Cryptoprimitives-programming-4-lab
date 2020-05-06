#pragma once
#include "MMATH.H"
#include "PointOnCurve.h"
#include "PolynomUtilities.h"

struct PointInProectiveCoordinats :public PointOnCurve
{
	M_LONG z;

	PointInProectiveCoordinats();

	PointInProectiveCoordinats(M_LONG _x, M_LONG _y, M_LONG _z);

	PointInProectiveCoordinats(PointOnCurve point);

	PointInProectiveCoordinats operator = (PointInProectiveCoordinats &a);

	bool operator == (PointInProectiveCoordinats &a);

	bool operator != (PointInProectiveCoordinats &a);

	bool isInfinityPoint();
};

ostream &operator <<(ostream &out, PointInProectiveCoordinats point);