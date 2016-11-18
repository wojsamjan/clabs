/* julia3.c                                                             */
/* third version of julia program 
/* takes several parameters as input, output in stdout                  */
/* complile as:                cc -lm -o julia julia3.c                 */
/* run as:                  ./julia -c colormaps/volcano.map/>file.ppm  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int rgb[256][3];
int x_res=200;
int y_res=200; 
float x_min=-2.0;
float x_max= 2.0;
float y_min=-2.0;
float y_max= 2.0;
float size  =2.0; 
float x_cen =0.0;
float y_cen =0.0;
double x,x_n,y,y_n;
double c=0.1;
double d=0.6;
int max_int = 255;

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

void help_list(){
  fprintf(stderr,"usage: julia -[wabxysnch] >file.ppm\n");
  fprintf(stderr," -a float [%4.3f]    real parameter      \n",c);
  fprintf(stderr," -b float [%4.3f]    imaginary parameter \n",d);
  fprintf(stderr," -w int   [%5d]    window pixel size     \n",x_res);
  fprintf(stderr," -x float [%4.3f]    phase space x center\n",x_cen);
  fprintf(stderr," -y float [%4.3f]    phase space y center\n",y_cen);
  fprintf(stderr," -s float [%4.3f]    size of phase space \n",size);
  fprintf(stderr," -c char  [%]        color map           \n","map");
  fprintf(stderr," -n int   [%5d]    maximal iterations    \n",255);
  fprintf(stderr," -h                  this help           \n");
  exit(1);
}

int optind=1;
int opterr=1;
char *optarg;

int main(int argc, char *argv[]){
  char   *options = "c:w:x:y:s:a:b:n:h";
  int    opt;
  FILE *map;
  int i,j,k,n;
  double dx,dy;
  int *color;

  for (i=0; i<256; i++) for (j=0; j<3; j++) rgb[i][j]=(256-i*j*111) % 256;
  while ( (opt=getopt(argc, argv, options)) != -1){
   switch(opt){
      case 'c': 
           if ((map = fopen(optarg,"r"))==NULL){ 
             fprintf(stderr,"Problem %s\n",argv[1]);exit(1);
           } else { get_colors(map); fclose(map); }
           break;
      case 'w':
           x_res=(int) atoi(optarg); y_res=x_res;
           break;
      case 'x':
           x_cen=atof(optarg);
           break;
      case 'y':
           y_cen=atof(optarg);
           break;
      case 's':
           size=atof(optarg); 
           x_min=x_cen-size; y_min=y_cen-size;
           x_max=x_cen+size; y_max=y_cen+size; 
           break;
      case 'a':
           c=atof(optarg);
           break;
      case 'b':
           d=atof(optarg);
           break;
      case 'n':
           max_int=atoi(optarg);
           break;
      case 'h':
           help_list();
           break;
    }                                             /*   end case list       */
  }

  fprintf(stdout,"P6\n%i %i\n255\n", x_res, y_res);
  dx = (x_max-x_min)/x_res; dy = (y_max-y_min)/y_res;

  for(j = 0; j < y_res; j++){
    for(k = 0; k < x_res; k++){
      n = 0; x = x_min + k*dx; y = y_max - j*dy;
      while( (x*x+y*y)<=4.0 && n++<max_int) { 
         x_n=x*x-y*y+c; y_n=2*x*y+d;x=x_n;y=y_n; 
      }
      n = (n < max_int) ? n%255 : 255;
      n = (n < 255) ? n + 1 : 0;
      color = &rgb[n][0];
      for(n = 0; n<3; n++) fputc(*color++,stdout); 
    }
  }
  return 0;
}
