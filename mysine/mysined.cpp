#include <cfloat>
#include <iostream>
#include "../ieee.h"    // Defines a sign() function
using namespace std;

double pi = 3.14159265358979323846; const int k = 10;
double pi1 = 3.1416015625, pi2 = -8.908910206761537356617e-6;

double mysine(double x) {
   int n = int(x/pi + 0.5*sign(x));
//   x -= n*pi;
   x -= n*pi1;
   x -= n*pi2;
   double num = x;
   double den = 1.0f;
   double sum = x;
   int fact = 1;  // The denominator contains fact!

   for (int i = 0; i < k; ++i) {
      num = -num*x*x;
      den *= ++fact;
      den *= ++fact;
      sum += num/den;
   }
   return (n%2) ? -sum : sum;
}

int main() {
   cout.precision(DBL_DIG-1);
   cout << mysine(0.0) << " (" << sin(0.0) << ")\n";
   cout << mysine(pi/2.0) << " (" << sin(pi/2.0) << ")\n";
   cout << mysine(pi) << " (" << sin(pi) << ")\n";
   cout << mysine(3.0*pi/2.0) << " (" << sin(3.0*pi/2.0) << ")\n";
   cout << mysine(22.0) << " (" << sin(22.0) << ")\n";
   cout << mysine(5.0e8) << " (" << sin(5.0e8) << ")\n";
}
