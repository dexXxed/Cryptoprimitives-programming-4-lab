#include "PointOnCurve.h"
#include "PolynomUtilities.h"

PointOnCurve::PointOnCurve() {
	x[0] = y[0] = 1;
	x[1] = y[1] = 0;
}

PointOnCurve::PointOnCurve(M_LONG _x, M_LONG  _y) {
	m_copy(x, _x);
	m_copy(y, _y);
}

bool PointOnCurve::operator == (PointOnCurve &a) {
	return !(m_cmp(x, a.x)) && !(m_cmp(y, a.y));
}

bool PointOnCurve::operator != (PointOnCurve &a) {
	return !(*this == a);
}

PointOnCurve PointOnCurve::operator =(PointOnCurve &a) {
	m_copy(x, a.x);
	m_copy(y, a.y);
	return *this;
}

bool PointOnCurve::isInfinityPoint() {
	return x[0] == 1 && x[1] == 0 && y[0] == 1 && y[1] == 0;
}

ostream &operator <<(ostream &out, PointOnCurve point) {
	if (point.isInfinityPoint()) {
		out << "  I  ";
		return out;
	}

	out << '(';
	printPolynomHex(out, point.x);
	out << ',';
	printPolynomHex(out, point.y);
	out << ')';
	return out;
}