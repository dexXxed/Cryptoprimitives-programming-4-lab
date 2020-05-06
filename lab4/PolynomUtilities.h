#pragma once

#include "MMATH.H"
#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::ostream;

int degree(M_LONG a);

void printPolynomHex(ostream &out, M_LONG a);

void setBits(M_LONG a, std::vector<unsigned int> degries);