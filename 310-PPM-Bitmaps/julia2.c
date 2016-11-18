/* julia2.c                                                             */
/* unlike julia1.c, this program 
/* allows color map as input, output is given in stdout                 */
/* complile as:                cc -lm -o julia julia2.c                 */
/* run as:                     ./julia colormaps/volcano.map/>file.ppm  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
double d=0.6;
int maximal_iteration = 255;

void get_colors(FILE *map){
int i,n = 0;
char buffer[80];
  while(fgets(buffer,80,map) && n < 256){
    rgb[n][0] = atoi(strtok(buffer," "));
    rgb[n][1] = atoi(strtok(NULL," "));
    rgb[n][2] = atoi(strtok(NULL," "));
    n++;
  }
  if (n<256) for(i=n; i<256;i++){rgb[i][0]=0;rgb[i][1]=0; rgb[i][2]=0;}
}

int main(int argc, char *argv[]){
  FILE *map;
  int i,j,k,n;
  double dx,dy;
  int *color;

  if (argc > 2){ fprintf(stderr,"usage: julia colormap\n"); exit(1); }
  if (argc < 2){ 
    for (i=0; i<256; i++) for (j=0; j<3; j++) rgb[i][j]=(256-i*j*111) % 256;
  } else {
    if ((map = fopen(argv[1],"r"))==NULL){
      fprintf(stderr,"Problem %s\n",argv[1]);exit(1);
    }
    get_colors(map); fclose(map);
  }

  fprintf(stdout,"P6\n%i %i\n255\n", x_res, y_res);
  dx = (x_max-x_min)/x_res; dy = (y_max-y_min)/y_res;

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
