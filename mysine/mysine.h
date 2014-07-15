/*
Ryan Justus
CNS 3320 � Numerical Software
Program 2
Elementary Functions
*/
#include <math.h>
#include <limits>
#include <float.h>
//Pi divided into PI1 and PI2
const double PI1 = 3.1416015625;
const double PI2 = 8.908910206761537356617e-06;

//Polynomial coefficients
const double C0 = -0.16666666666666665052;
const double C1 = 0.83333333333331550314e-02;
const double C2 = -0.19841269841201840457e-03;
const double C3 = 0.27557319210152756119e-05;
const double C4 = -0.25052106798274584544e-07;
const double C5 = 0.16058936490371589114e-09;
const double C6 = -0.76429178068910467734e-12;
const double C7 = 0.27204790957888846175e-14;

int sign_bit(double x){
	unsigned long long* num = reinterpret_cast<unsigned long long*>(&x);
	unsigned long long mask = 1ul;
	mask=mask<<63;
	return (int)(!!(*num & mask));
}

double mysine(double x){
	//1. If our argument, x, is 1 or a NaN, return NaN.
	if(isnan(x) || !isfinite(x)){
		return x;
	}
	
	//2. If x > 10^9, return a NaN.
	if(x>pow(10,9)){
		return NAN;
	}
	
	//3. Reduce x by a factor of n*pi to t where -pi/x <= t <= pi/x 
	// (use the two-step procedure with pi1 and pi2 explained earlier). Record n.
	int sign= (sign_bit(x)) ? -1 : 1;
	long n = long(x/PI1 + 0.5*sign);
	x-=n*PI1;
	x-=n*PI2;
	int even_odd = (n%2==0) ? 1:-1;
	
	//4. If t^2 < epsilon, return +-t, depending on whether n is even or odd.
	if(pow(x,2)<DBL_EPSILON){
		return x*even_odd;
	}
	
	//5. Compute sin t by Horner's Rule as explained above.
	//For performance I unrolled the loop	
	double y = x*x;
	double sum =C7*y;
	sum+=C6+y*sum;
	sum+=C5+y*sum;
	sum+=C4+y*sum;
	sum+=C3+y*sum;
	sum+=C2+y*sum;
	sum+=C1+y*sum;
	sum+=C0+y*sum;
	sum*=x;
	
	//6. If n is even, return the result from the previous step. Otherwise, returns its negation.
	return sum*even_odd;
}
