#include "PointInProectiveCoordinats.h"

PointInProectiveCoordinats::PointInProectiveCoordinats() {
	PointOnCurve();
	z[0] = 1;
	z[1] = 0;
}

PointInProectiveCoordinats::PointInProectiveCoordinats(M_LONG _x, M_LONG _y, M_LONG _z) {
	m_copy(x, _x);
	m_copy(y, _y);
	m_copy(z, _z);
}

PointInProectiveCoordinats::PointInProectiveCoordinats(PointOnCurve point) {
	m_copy(x, point.x);
	m_copy(y, point.y);
	z[0] = 1;
	z[1] = 1;
}

PointInProectiveCoordinats PointInProectiveCoordinats::operator = (PointInProectiveCoordinats &a) {
	PointOnCurve::operator=(a);
	m_copy(z, a.z);
	return *this;
}

bool PointInProectiveCoordinats::operator == (PointInProectiveCoordinats &a) {
	return PointOnCurve::operator==(a) && !m_cmp(z, a.z);
}

bool PointInProectiveCoordinats::operator != (PointInProectiveCoordinats &a) {
	return !(*this == a);
}

bool PointInProectiveCoordinats::isInfinityPoint() {
	for (int i = z[0]; i > 0; i--)
		if (z[i])
			return false;

	return true;
}

ostream &operator <<(ostream &out, PointInProectiveCoordinats point) {
	if (point.x[0] == 0 || point.y[0] == 0) {
		out << "   I   ";
		return out;
	}

	out << '(';
	printPolynomHex(out, point.x);
	out << ',';
	printPolynomHex(out, point.y);
	out << ',';
	printPolynomHex(out, point.z);
	out << ')';
	return out;
}