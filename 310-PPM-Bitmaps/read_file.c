/* reads integers from "integer.file", real numbers from real.file   */

#include <stdio.h>

int main (void) {  
   FILE *file1, *file2;
   int i;
   double r;

   file1 = fopen ("integer.file", "r"); 
   while (fscanf (file1, "%d", &i) != EOF) { printf("%10d\n",i); }
   fclose (file1);

   file2 = fopen ("real.file", "r");
   while(fscanf (file1, "%lf", &r) != EOF) { printf ("%10.5f\n",r); }
   fclose (file2);

   return 0;
}
