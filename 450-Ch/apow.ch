/* 
   Kilka dzia³añ na tablicach.
   
   Wszystko jasne?
*/

#include <numeric.h>  // zawiera `array'

#define NUMPOINTS 4
int main() {
    array double x[NUMPOINTS];
    array double y[NUMPOINTS] = (array int [NUMPOINTS])3;
    linspace(x,1,NUMPOINTS);
    printf("x = %.1f",x);
    printf("y = %.1f",y);
    printf("x^y = %.1f",pow(x,y));
    printf("y^x = %.1f",pow(y,x));
}
