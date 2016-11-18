/* oblicz szerokość pola dla printf */

#include <stdio.h>
#include <string.h>

#define LOWER 300000 /* dolna granica temperatur */
#define UPPER 300100 /* górna granica */
#define STEP 20 /* rozmiar kroku */

int main() {
  int fahr;
  char max_int[80]; /* należy wyliczyć! */
  char max_float[80]; /* należy wyliczyć! */
  char format[80]; /* należy wyliczyć! */

  sprintf(max_int,"%d",UPPER);
  sprintf(max_float,"%.1f",(5.0/9.0)*(UPPER-32));
  sprintf(format,"%%%dd %%%d.1f\n",strlen(max_int)+3,strlen(max_float)+3);
  printf("%s\n",format);

  for (fahr=LOWER; fahr<=UPPER; fahr=fahr+STEP) {
    printf(format,fahr,(5.0/9.0)*(fahr-32));
  }
}
