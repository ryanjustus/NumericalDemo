// mysine2.cpp: Calculates sin x. Uses long long.
// Uses a truncated, economized Taylor Polynomial,
// evaluated by Horner's rule. Rejects large angles
// (|x| > 10^15). Reduces the argument to the range
// [-pi/2, pi/2]. Uses 1.5 precision by splitting pi
// into two components (see pi1, pi2, below).
// Returns +/-x if |x| < sqrt(eps).

// Author: C. Allison, February, 2006

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <float.h>
#include "../ieee.h"
using namespace std;

const double piovertwo = 1.57079632679489661923;
const double pi = 3.14159265358979323846;
const double twopi = 6.28318530717958647693;
const double pi1 = 3.1416015625;
const double pi2 = -8.908910206761537356617e-6;
long double oneoverpi = 0.31830988618379067154L;
const int k = 9; 

// The Cody & Waite coefficients for double precision
double c[k] = {
    1.0,
   -0.16666666666666665052,
    0.83333333333331550314e-2,
   -0.19841269841201840457e-3,
    0.27557319210152756119e-5,
   -0.25052106798274584544e-7,
    0.16058936490371589114e-9,
   -0.76429178068910467734e-12,
    0.27204790957888846175e-14
};

double mysine(double x) {
	//1. If our argument, x, is 1 or a NaN, return NaN.
	if(isnan(x) || !isfinite(x)){
		return NAN;
	}
	
	//2. If x > 10^9, return a NaN.
	if(x>pow(10.0f,9)){
		return NAN;
	}	
	//3. Reduce x by a factor of n*pi to t where -pi/x <= t <= pi/x 
	// (use the two-step procedure with pi1 and pi2 explained earlier). Record n.
	int sign= (sign_bit(x)) ? -1 : 1;
	int n = (int)(x*oneoverpi+0.5*sign);
	x-=n*pi1;
	x-=n*pi2;
	int even_odd = (n%2==0) ? 1:-1;
	
	//4. If t^2 < epsilon, return +-t, depending on whether n is even or odd.
	if(pow(x,2)<DBL_EPSILON){
		return x*even_odd;
	}
	
	//5. Compute sin t by Horner's Rule as explained above.
	double y = x*x;
	double sum=0;
	for(int i=k-1;i>=0;i--){
		sum=c[i]+y*sum;
	}
	sum*=x;
	
	//6. If n is even, return the result from the previous step. Otherwise, returns its negation.
	return sum*even_odd;
}

void test(double x) {
   double mine = mysine(x);
   double theirs = sin(x);
   cout << "mysine(" << x << ") = " << mine << endl;
   cout << "sin(" << x << ") = " << theirs << endl;
   if (!is_nan(mine)) {
       cout << "ulps difference = " << ulps(mine, theirs) << endl;
       if (theirs != 0.0) {
           if (sign(mine)*sign(theirs) < 0) {
               cout << "ulps difference of magnitudes = "
                    << ulps(abs(mine),abs(theirs)) << endl;
               cout << "relative error of magnitudes = "
                    << abs((abs(mine)-abs(theirs))/theirs) << endl;
           }
           else
               cout << "relative error = " << abs((mine-theirs)/theirs) << endl;
       }
   }
   cout << endl;
}

void special_test() {
   test(22.0);
   double mine = mysine(22.0);
   double correct = -8.85130929040388e-3;
   cout << "mysine(" << 22 << ") = " << mine << endl;
   cout << "correct sin(" << 22 << ") = " << correct << endl;
   cout << "ulps difference = " << ulps(mine, correct) << "\n\n";
}

int main() {
   cout.precision(numeric_limits<double>::digits10);
   test(0.0);
   test(piovertwo);
   test(pi);
   test(3.0*piovertwo);
   test(twopi);
   test(3.0*pi);
   test(1.43482145895292);
   special_test();
   test(1.0e9);
   test(piovertwo*1.0e7);
   test(piovertwo*1.0e8);
   test(piovertwo*1.0e9);
   test(piovertwo*1.0e10);
   test(piovertwo*1.0e30);
   test(3.14e30);
   test(-1.0e-30);
   test(1.0e15);
   test(1.0e14);
}
