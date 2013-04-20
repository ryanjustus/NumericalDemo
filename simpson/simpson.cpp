#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>
#include <limits>
#include <float.h>

using namespace std;

int nevals;

double f1(double x) {
   nevals++;
   return exp(x*x);
}

double f2(double x){
	nevals++;
	if(abs(x) <= DBL_EPSILON){
		return 1.0;
	}
	return sin(x)/x;
}

/**
* recursively compute area
*	a = left point, m = middle point, b = right point
*	A1 = area of previous round
*/
double area_r(double a, double fa,
			  double m, double fm, 
			  double b, double fb,
			  double A1, double f(double), double tol){	
	double m1 = (a+m)/2.0;	float fm1 = f(m1); //midpoint between a and m
	double m2 = (m+b)/2.0;	float fm2 = f(m2); //midpoint between m and b
	//compute A2;	
	double Aa = (m-a)/6.0*(fa+4.0*fm1+fm); //Area from a to m
	double Ab = (b-m)/6.0*(fm+4*fm2+fb); //Area from m to b
	double A2 = Aa+Ab;
	double err = (A2-A1)/15.0;
	if(abs(err) <= tol){
		return (A2 + err);
	}else{
		return area_r(a,fa,m1,fm1,m,fm,Aa,f, tol) + area_r(m, fm, m2, fm2, b, fb,Ab,f, tol);
	}
}

double area(double a, double b, double f(double), double tol){
	double fa = f(a);
	double fb = f(b);
	double m = (a+b)/2.0;
	double fm = f(m);
	double A1 = (b-a)/6.0*(fa+4.0*fm+fb);
	return area_r(a,fa,m,fm,b,fb,A1,f,tol);
}

int main(int argc, char* argv[]) {
	double tol = 1.0e-06;
	printf("tol = %f\n", tol);
	
	nevals=0;
	double a = area(-1.0,1.0, f1,tol);
	printf("(nevals = %d) e^(x^2) [-1,1] = %.9f\n",nevals, a);
	//2.925303493
	
	nevals=0;
	a = area(-1.0,10.0,f2,tol);
	printf("(nevals = %d) sin(x)/x [-1,10] = %.9f\n",nevals, a);
	//2.604430664
	
	nevals=0;
	a = area(0.0,1.0,f2,tol);
	printf("(nevals = %d) sin(x)/x [0,1] = %.9f\n",nevals, a);	
	fflush(stdout);
	//0.9460830694
}
