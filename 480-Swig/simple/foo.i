%module foo

%inline %{
extern double bar;
/* funkcje z standardowej biblioteki math.h */
extern double sin(double x);
extern int strcmp(const char *, const char *);
%}

/*  stałe  */
%constant double Bar = 1.6180;
#define STATUS 1001
#define VERSION "0.1alpha"
