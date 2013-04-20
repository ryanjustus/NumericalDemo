/*
program 3 numerical
C++ zero(double a, double b, double f())
*/

#include <limits>
#include <iostream>
#include <cmath>

#define swap(type, a, b) {type t=a; a=b; b=t;}
 

//function prototypes
double secantZero(double a, double fa, double f, double fb);
double bisect(double a, double b);
int sign(double x);

double zero(double a, double b, double f()){

	double fa = f(a);
	int sign_a = sign(a);
	
	double fb = f(b);
	int sign_b = sign(b);
	
	
	while(b-a > abs(b)*eps && fa!=0 && fb!=0){
		if(fa==0){
			return a;
		}
		if(fb==0){
			return b;
		}
		double c = secantZero(a,fa,b,fb);
		double fc = f(c);
		if(fc==0){
			return c;
		}
		int sign_c = sign(c);
		
		//if sign(a)=sign(c), use secant between (a,f(a)) and (c,f(c)), otherwise use (c,f(c)) and (b,f(b))
		double d = (sign_a==sign_c) ? secantZero(a,fa,c,fc) : secantZero(c,fc,b,fb);
		double fd;
		int sign_d;
		
		//if d is outside of [a,b] use bisect(a,c) or bisect(c,b)
		if( d<a || d>b){
			d = (sign_a != sign_c) ? bisect(a,c) : bisect(c,b);
			fd = f(d);
			sign_d = sign(d);
		}
		
		//otherwise the new cantidate interval is either [c,d] or [d,c]
		else{	
			if(sign_a != sign_c){
				//switch c,d if the interval was d,c
				swap(double, c,d);	
				swap(double, fc,fd);
				swap(int, sign_c,sign_d);			
			}
			//If we aren't less than half of [a,b], do a bisection
			if( (b-a)/2 > (d-c) ){
				double e = bisect(c,d);
				double fe = f(e);
				int sign_e = sign(e);
				if(sign_e == sign_c){
					//replace c with e
					c=e;
					fc=fe;
					sign_c=sign_e;
				}else{
					//replace d with e
					d=e;
					fd=fe;
					sign_d=sign_e;
				}
			}		
		}
		//Set a and b to new interval
		a=c;
		fa=fc;
		sign_a=sign_c;
		b=d;
		fb=fd;
		sign_b = sign_d;
	}
	//return the smaller of the endpoints
	return (fa < fb ? a : b);
	
}

double secantZero(double a,double fa,double b,double fb){
	c = a - fa*(b-a)/(fb-ba)
}

double bisect(double a,double b){
	double dist = (a+b)/2;
}

double checkZero(double a,double b){
	return b-a < abs(a)*numeric_limits<double>::epsilon();
}

int sign(double a){
	return (a>0) ? 1 : ((a<0) ? -1 : 0);
}


