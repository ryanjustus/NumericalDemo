/*
Ryan Justus
CNS 3320 – Numerical Software
Program 2
Elementary Functions
*/

static const double nan = sqrt(-1.0);
static const double inf = 1.0/0.0;

double mysine(double x){
//1. If our argument, x, is 1 or a NaN, return NaN.

//2. If jxj > 109, return a NaN.
//3. Reduce x by a factor of n*pi to t where -pi/x <= t <= pi/x
//2 (use the two-step procedure with pi1 and pi2 explained earlier). Record n.
//4. If t^2 < epsilon, return +-t, depending on whether n is even or odd.
//5. Compute sin t by Horner's Rule as explained above.
//6. If n is even, return the result from the previous step. Otherwise, returns its negation.
	return 0;
}