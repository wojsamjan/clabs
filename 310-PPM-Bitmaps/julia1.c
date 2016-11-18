/* julia1.c                                                    */
/* simplest version of program which produces julia set        */
/* no input, output in stdout                                  */
/* complile as:                cc -lm -o julia julia.c         */
/* run as:                     ./julia>file.ppm                */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rgb[256][3];
int x_res=1000;
int y_res=1000; 
float x_min=-2.0;
float x_max= 2.0;
float y_min=-2.0;
float y_max= 2.0;
double x,x_n,y,y_n;
double c=0.1;
double d=0.7;
int maximal_iteration = 255;

int main(){
  int i,j,k,n;
  double dx,dy;
  int *color;
  for (i=0; i<256; i++) for (j=0; j<3; j++) rgb[i][j]=(256-i*j*111) % 256;
  fprintf(stdout,"P6\n%i %i\n255\n", x_res, y_res);
  dx = (x_max - x_min)/x_res; dy = (y_max - y_min)/y_res;
  for(j = 0; j < y_res; j++){
    for(k = 0; k < x_res; k++){
      n = 0; x = x_min + k*dx; y = y_max - j*dy;
      while( (x*x+y*y)<=4.0 && n++<maximal_iteration) { 
         x_n=x*x-y*y+c; y_n=2*x*y+d;x=x_n;y=y_n; 
      }
      n = (n < maximal_iteration) ? n%255 : 255;
      n = (n < 255) ? n + 1 : 0;
      color = &rgb[n][0];
      for(n = 0; n<3; n++) fputc(*color++,stdout); 
    }
  }
  return 0;
}
