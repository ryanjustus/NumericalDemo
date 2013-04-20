#include <iostream>
#include "../ieee.h"    // Defines a sign() function
using namespace std;

double pi = 3.14159265358979323846; const int k = 5;
double pi1 = 3.1416015625, pi2 = -8.908910206761537356617e-6;

float mysine(float x) {
   int n = int(x/pi + 0.5*sign(x)); // Use double precision here
//   x -= n*pi;
   x -= n*pi1;
   x -= n*pi2;
   float num = x;
   float den = 1.0f;
   float sum = x;
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
   cout << mysine(0.0f) << " (" << sin(0.0f) << ")\n";
   cout << mysine(pi/2.0f) << " (" << sin(pi/2.0f) << ")\n";
   cout << mysine(pi) << " (" << sin(pi) << ")\n";
   cout << mysine(3.0f*pi/2.0f) << " (" << sin(3.0f*pi/2.0f) << ")\n";
   cout << mysine(22.0f) << " (" << sin(22.0f) << ")\n";
   cout << mysine(5.0e8f) << " (" << sin(5.0e8f) << ")\n";
}
