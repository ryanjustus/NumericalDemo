/*
Ryan Justus
CNS 3320 – Numerical Software
Program 1
IEEE Floating Point Numbers
*/
#include <math.h>
#include <iostream>

using namespace std;

//Function prototypes
bool is_subnormal(double x);
double fraction(double x);


//In this assignment you will write a number of functions that facilitate the use and inspection of floating-point numbers encoded according to IEEE 754. You will only need to provide double versions of the following. Your functions should work identically on both big-endian and little-endian platforms, which will come for free if you use bitwise operations only and not make assumptions about byte ordering. Make these efficient as possible. You will need to use C++ and unsigned long long for this assignment.
//sign 1 bit, exponent 11 bits, fraction is 52 bits
//returns the sign bit of x as-is (i.e., 0 or 1).
inline
int sign_bit(double x){
	unsigned long long* num = reinterpret_cast<unsigned long long*>(&x);
	unsigned long long mask = 1ul;
	mask=mask<<63;
	return (int)(!!(*num & mask));
}

//returns -1 if the x is negative, 0 if x is (either positive or negative) zero, 1 if x is positive.
inline
int sign(double x){
	if(x==0){
		return 0;
	}else if(sign_bit(x)){
		return -1;
	}else{
		return 1;
	}
}

//returns the unbiased binary exponent of x as a decimal integer. Remember that subnormals are a special case. Consider 0 to be a subnormal.
inline
int exponent(double x){
	unsigned long long num = *reinterpret_cast<unsigned long long*>(&x);
	unsigned long long mask = 0x07FFull;
	mask=mask<<52;
	int expVal = (num&mask)>>52;
	expVal-=1023;
	if(!fraction(x) && expVal==-1023){
		expVal+=1;
	}
	return expVal;     	
}	

//returns the IEEE fractional part of x as a decimal floating-point number. You must convert binary to decimal.
inline
double fraction(double x){
	unsigned long long num = *reinterpret_cast<unsigned long long*>(&x);
	unsigned long long mantissa_mask = 0x01FFFFFFFFFFFFFull; //52 1's
	unsigned long long exponent_mask = (0x03FFull<<52); //Put 1023 into exponent
	num&=mantissa_mask;
	num|=exponent_mask;	
	return *reinterpret_cast<double*>(&num)-1; 
}

//returns the full IEEE mantissa of x as a decimal floating-point number (which is the same as fraction() + 1  for normalized numbers; same as fraction() for subnormals).
inline
double mantissa(double x){	
	double mantissaD = fraction(x)+1;	
	if(is_subnormal(x)){
		mantissaD-=1;
	}
	return mantissaD; 
}

//returns true if x is a normalized floating-point number, false otherwise. Subnormals (including 0), NaNs and infinities return false.
inline
bool is_normal(double x){
	int expVal = exponent(x);
	return(expVal!=1024 && expVal!=-1022); 
}

//returns true if x is a sub-normal floating-point number (including zero), false otherwise.
inline
bool is_subnormal(double x){
	int e = exponent(x);
	return(e==-1022); 
}

//returns a copy of x with the same sign bit as y, except if y is zero, leaves the copy of x unchanged.
inline
double copysign(double x, double y){
	double num = x;
	int signX = sign(x);
	int signY = sign(y);
	if(y!=0 && signX!=signY){
		num*=-1;
	}	
	return num;
}

//returns true if x is any type of NaN.
inline
bool is_nan(double x){
	double m = mantissa(x);
	int e = exponent(x);
	return (e==1024 && m!=0);
}

//returns true if x is positive or negative infinity
inline
bool is_infinity(double x){
	double m = mantissa(x);
	int e = exponent(x);
	return ((e==1024) && m==1);
}

//returns true if x is positive infinity
inline
bool is_posinfinity(double x){
	if(is_infinity(x)){
		return !sign_bit(x);
	}else{
		return 0;
	}
}

//returns true if x is negative infinity
inline
bool is_neginfinity(double x){
	if(is_infinity(x)){
		return sign_bit(x);
	}else{
		return 0;
	}	
}

//(obvious – and NaNs return false)
inline
bool is_finite(double x){
	return !(is_infinity(x) || is_nan(x));
}

//The following is for convenience, although not specifically IEEE related.
//returns the magnitude of the spacing between x and its floating-point successor (you may use pow(), or preferably, ldexp(), to compute this if you wish.).
inline
double ulp(double x){
    // Handle special cases
    if (is_nan(x) || is_infinity(x)){
       return x;   
	}

    // Convert to long and add 1
    unsigned long long next = *reinterpret_cast<long long*>(&x)+1;
	
	// Convert next back to double
	double nextD = *reinterpret_cast<double*>(&next);
	
	// subract values
	double ulp = nextD-x;
	if(ulp<0)
		ulp*=-1;
	return ulp;
}

inline
long ulps(double d1, double d2){
	long l1 = *reinterpret_cast<long*>(&d1);
	long l2 = *reinterpret_cast<long*>(&d2);
	return abs(l1-l2);
}
