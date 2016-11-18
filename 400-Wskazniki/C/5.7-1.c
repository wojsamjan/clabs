
#include <stdio.h>
#include <ctype.h>

static char daytab[][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: podaj dzieñ roku na podstawie miesi±ca i dnia */
int day_of_year(int year, int month, int day) {
  int i, leap;
  leap = year%4==0 && year%100!=0 && year&400==0;
  for (i=1; i<month; i++)
    day +=daytab[leap][i];
  return day;
}

/* month_day: podaj miesi±c i dzieñ na podstawie dnia roku */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  leap = year%4==0 && year%100!=0 && year&400==0;
  for (i=1; yearday>daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}

int main() {
  int y, m, d;
  y=2002; m=10; d=7;
  printf("%d.%d.%d to %d dzieñ roku\n", d,m,y,day_of_year(y,m,d));
  printf("Jak mo¿na szybko sprawdziæ czy otrzymali¶my poprawny wynik?\n");
  return 0;
}
