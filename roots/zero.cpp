/*
program 3 numerical
C++ zero(double a, double b, double f())
*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#define swap(type, a, b) {type t=a; a=b; b=t;}

using namespace std;
 

//function prototypes
double secantZero(double a, double fa, double f, double fb);
double bisect(double a, double b);
int sign(double x);
double eps = numeric_limits<double>::epsilon();
int nevals;


double zero(double a, double b, double f(double)){
	nevals=0;
	double fa = f(a);
	int sign_a = sign(fa);
	
	double fb = f(b);
	int sign_b = sign(fb);	
	double c;
	
	int loops =0 ;
	
	//While the interval is greater than 1 ulp and neither endpoint is zero
	while(b-a > fabs(b)*eps && fa!=0 && fb!=0){
		cout << "\titer " << ++loops <<  ": " << "nevals="<< nevals<< endl;
		cout << "\t\ta="<<a<< ", f(a) = " << fa << endl;
		cout << "\t\tb="<<b<< ", f(b) = " << fb << endl;
		c = secantZero(a,fa,b,fb);
		double fc = f(c);
		if(fc==0){
			cout << "\troot found at c=" << c << endl;
			return c;
		}		
		int sign_c = sign(fc);
		cout << "\t\tc=" << c<< ", f(c)=" << fc  << endl;
		
		//if sign(a)=sign(c), use secant between (a,f(a)) and (c,f(c)) to find d, otherwise use (c,f(c)) and (b,f(b))
		double d = (sign_a==sign_c) ? secantZero(a,fa,c,fc) : secantZero(b,fb,c,fc);
		double fd;
		int sign_d;		
		
		//if d is outside of [a,b] use bisect(a,c) or bisect(c,b)
		if( d<=a || d>=b){
			cout << "\t\td<=a || d>=b" << endl;
			d = (sign_a != sign_c) ? bisect(a,c) : bisect(c,b);
			fd = f(d);
			if(fd==0){
				cout << "\troot found at d=" << d << endl;
				return d;
			}			
			sign_d = sign(fd);
			cout << "\t\td=" << d<<", f(d)="<< fd <<  endl;
		}
		
		
		//otherwise the new cantidate interval is either [c,d] or [d,c]
		else{
			fd = f(d);
			if(fd==0){
				cout << "\troot found at d=" << d << endl;
				return d;
			}			
			sign_d = sign(fd);
			cout << "\t\td=" << d<<", f(d)="<< fd << endl;
			if(sign_a != sign_c){
				//switch c,d if the interval was d,c
				swap(double, c,d);	
				swap(double, fc,fd);
				swap(int, sign_c,sign_d);			
			}
			//If we aren't less than half of [a,b], do a bisection
			if( (b-a)/2 <= (d-c) ){
				cout << "\t\t(b-a)/2 < (d-c)" << endl;
				double e = bisect(c,d);
				double fe = f(e);
				if(fe==0){
					cout << "\troot found at e=" << e << endl;
					return e;
				}
				int sign_e = sign(fe);				
				
				cout << "\t\te=" << e << ", f(e)" << fe << endl;
				if(sign_e == sign_c){
					//replace c with e
					cout << "\t\treplace c with e" << endl;
					c=e;
					fc=fe;
					sign_c=sign_e;
					cout << "\t\tc=" << c << ", f(c)" << fc << endl;
				}else{
					//replace d with e
					cout << "\t\treplace d with e" << endl;
					d=e;
					fd=fe;
					sign_d=sign_e;
					cout << "\t\td=" << d << ", f(d)" << fd <<endl;
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
	
	cout << "\tfinal: (" << a <<',' << fa <<") to ("<< b << ',' << fb <<')'<< endl;
	//return the smaller of the endpoints
	return (fabs(fa) < fabs(fb) ? a : b);
	
}

// A function whose root we wish to find in some range
double f(double x) {
   nevals++;
   return x*cos(x) + sin(x);
}

// A function whose root we wish to find in some range
double g(double x) {
   nevals++;
   return exp(-x) - x;
}

int main(){
	cout.precision(numeric_limits<double>::digits10);
	//First root x*cos(x) + sin(x)
	cout << "f(x) = x*cos(x) +sin(x)" << endl;
	cout << "1st root" << endl;
	double a = 1.0, b = 3.0;
	double root = zero(a, b, f);
	cout << nevals << " function calls" << endl;	
	cout << "r=" << root << ", f(r)=" << f(root) << endl;
	cout << endl <<endl;
	
	//Second root x*cos(x) + sin(x)
	cout << "f(x) = x*cos(x) +sin(x)" << endl;
	cout << "2nd root" << endl;
	a = 4.5;
	b = 5.5;
	root = zero(a, b, f);
	cout << nevals << " function calls" << endl;	
	cout << "r=" << root << ", f(r)=" << f(root) << endl;
	cout << endl <<endl;
	
	//First root e^-x -x
	cout << "g(x) = e^(-x) - x" << endl;
	cout << "1st root" << endl;
	a = 0.1;
	b = 0.9;
	root = zero(a, b, g);
	cout << nevals << " function calls" << endl;	
	cout << "r=" << root << ", g(r)=" << g(root) << endl;

}

double secantZero(double a,double fa,double b,double fb){
	double slope = (fb-fa)/(b-a);
	double c =  a - fa/slope;
	//if we are to the right or left of [a,b] move in 1-2 ulps 
	/*
	if(c<=a){
		c+=fabs(c)*eps;
	}else if(c>=b){
		c-=fabs(c)*eps;
	}
	*/
	return c;
}

double bisect(double a,double b){
	cout << "\t\tbisecting " << a << "->" << b << endl;
	return (a+b)/2;
}

int sign(double a){
	return (a>0) ? 1 : ((a<0) ? -1 : 0);
}


