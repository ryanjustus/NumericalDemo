// ieee.cpp: Test program for ieee.h
#include <cassert>
#include <iostream>
#include <limits>
#include "ieee.h"
using namespace std;

int main() {
   double y = 6.5;

   assert(sign_bit(y) == 0);
   assert(sign_bit(0.0) == 0);
   assert(sign_bit(-y) == 1);
   assert(sign(y) == 1);
   assert(sign(0.0) == 0);
   assert(sign(-y) == -1);
   assert(sign(-0.0) == 0);
   assert(exponent(y) == 2);
   assert(exponent(16.5) == 4);
   assert(!is_normal(0.0));
   assert(is_subnormal(0.0));
   assert(is_normal(6.5));
   assert(!is_subnormal(6.5));
   assert(fraction(y) == 0.625);
   assert(fraction(0.0) == 0.0);
   assert(mantissa(y) == 1.625);
   assert(mantissa(0.0) == 0.0);
   double nan = sqrt(-1.0);
   double inf = 1.0/0.0;
   assert(exponent(nan) == 1024);
   assert(exponent(0.0) == -1022);
   assert(is_posinfinity(inf));
   assert(!is_neginfinity(inf));
   assert(!is_posinfinity(-inf));
   assert(is_neginfinity(-inf));
   assert(!is_finite(-inf));
   assert(is_finite(1.0));
   assert(is_nan(nan));
   assert(is_nan(-nan));
   cout << "ulp(6.5) == " << ulp(6.5) << endl;
   cout << "ulp(1.0) == " << ulp(1.0) << endl;
   cout << "ulp(0.0) == " << ulp(0.0) << endl;
   cout << "ulp(0.5) == " << ulp(0.5) << endl;
   cout << "ulp(-0.5) == " << ulp(-0.5) << endl;
   cout << "ulp(dmin) == " << ulp(numeric_limits<double>::denorm_min()) << endl;
   assert(copysign(6.5, -1.0) == -6.5);
   assert(copysign(-6.5, 1.0) == 6.5);
   assert(copysign(-inf, 1.0f) == inf);
   cout << "ulp(1.0e15) == " << ulp(1.0e15) << endl;
   cout << "ulp(1.0e16) == " << ulp(1.0e16) << endl;
}

/* Expected Output:
ulp(6.5) == 8.88178e-16
ulp(1.0) == 2.22045e-16
ulp(0.0) == 4.94066e-324
ulp(0.5) == 1.11022e-16
ulp(dmin) == 4.94066e-324
ulp(1.0e15) == 0.125
ulp(1.0e16) == 2
*/



