#include "PolynomUtilities.h"

int degree(M_LONG a) {
	for (int i = 32 * a[0] - 1; i >= 0; i--)
		if ((a[i / 32 + 1] >> (i % 32)) & 1)
			return i;

	return -1;
}

void printPolynomHex(ostream &out, M_LONG a) {
	int firstNotZerro = a[0];

	while (firstNotZerro > 0 && a[firstNotZerro] == 0)
		firstNotZerro--;

	if (!firstNotZerro) {
		out << '0';
		return;
	}

	out << hex << a[firstNotZerro];

	for (int i = firstNotZerro - 1; i > 0; i--)
		out << std::setw(8) << std::setfill('0') << a[i];

	out << dec << std::setw(0);
}

void setBits(M_LONG a, std::vector<unsigned int> degries) {
	for (int i = 0; i < degries.size() - 1; i++)
		if (degries[i] <= degries[i + 1]) {
			cout << "Некорректный полином" << endl;
			return;
		}

	a[0] = degries[0] / 32 + 1;

	for (int i = 1; i <= a[0]; i++)
		a[i] = 0;

	for (int i = 0; i < degries.size(); i++)
		a[degries[i] / 32 + 1] |= 1 << (degries[i] % 32);
}