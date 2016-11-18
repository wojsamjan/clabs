/* writes random integers to "integer.file", random reals to "real.file"   */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#define MAX_R  2147483647
#define N 100

int main (void) { 
   FILE  *file1, *file2; 
   int i;
   srand(time ((time_t *) 0) );

   file1 = fopen ("integer.file", "w"); 
   for (i=1;i<=N;i++) fprintf(file1,"%d\n",rand()); 
   fclose(file1);

   file2 = fopen ("real.file", "w"); 
   for (i=1;i<=N;i++) fprintf(file2, "%f\n",rand()/(1.0*MAX_R));
   fclose(file2);

   return 0;
}
