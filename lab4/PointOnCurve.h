#pragma once
#include "MMATH.H"
#include <iostream>

using std::ostream;

struct PointOnCurve
{
	M_LONG x;
	M_LONG y;

	PointOnCurve();

	PointOnCurve(M_LONG _x, M_LONG  _y);

	bool operator == (PointOnCurve &a);

	bool operator != (PointOnCurve &a);

	PointOnCurve operator =(PointOnCurve &a);

	bool isInfinityPoint();

};

ostream &operator <<(ostream &out, PointOnCurve point);
