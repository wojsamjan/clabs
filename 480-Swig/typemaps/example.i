%module example

%include "typemaps.i"

%apply double *OUTPUT { double *result };
%inline %{
extern void add(double a, double b, double *result);
%}

%apply int *OUTPUT { int *width, int *height };
%inline %{
extern void getwinsize(int winid, int *width, int *height);
%}

/* example_wrap.c:1777: warning: dereferencing type-punned pointer will break strict-aliasing rules */

%{
extern void negate(double *);
%}
extern void negate(double *INOUT);

