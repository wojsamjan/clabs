
// Designated initializers make working with structs much easier,
// to the point that I’ve almost entirely stopped using the old method.
// Instead of illegible and errorprone junk like
//
//  person_struct p = {"Joe", 22, 75, 20},
//
// we can write selfdocumenting declarations such as
//
//  person_struct p = {.name="Joe", .age=22, .weight_kg=75, .education_years=20}.
//
// Ben Klemens, 21st Century C,
// http://oreilly.com/catalog/errata.csp?isbn=9781449327149

#include <stdio.h>
#include <strings.h> // strcasecmp
#include <math.h>    // NAN

// typedef struct {
//  double width;
//  double height;
// } size_s;

// albo krócej

typedef struct {
  double width, height;
} size_s;

// funkcja zwracająca strukturę

size_s width_height(char *papertype){
  return
      !strcasecmp(papertype, "A4")     ? (size_s) {.width=210, .height=297}
    : !strcasecmp(papertype, "Letter") ? (size_s) {.width=216, .height=279}
    : !strcasecmp(papertype, "Legal")  ? (size_s) {.width=216, .height=356}
                                       : (size_s) {.width=NAN, .height=NAN};
}

int main(){
  size_s a4size = width_height("a4");
  printf("width = %g, height = %g\n", a4size.width, a4size.height);
}

// albo zwracamy height i width korzystając z wskaźników
// void width_height(char *papertype, double *width, double *height);

// albo zwracamy width i height korzystajac ze wskaźnika:
// double width_height(char *papertype, double *height);
