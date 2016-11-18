#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void copy_removing_comments(FILE *in, FILE *out);

int main() {
  copy_removing_comments(stdin, stdout);
}

void copy_removing_comments(FILE *in, FILE *out) {
  int c, nc;
  int comment_flag = FALSE;

  while ((c = fgetc(in)) != EOF) {
    if (comment_flag) {
      if (c == '*') {
        nc = fgetc(in);
        if (nc == '/')
          comment_flag = FALSE;
        else
          ungetc(nc, in);
      }
    } else {
      if (c == '/') {
        nc=fgetc(in);
        if (nc == '*')
          comment_flag = TRUE;
        else
          ungetc(nc, in);
      }
      if (!comment_flag)
        fputc(c, out);
    }
  }
}
