#include <stdio.h>

#define FALSE 0
#define TRUE 1

void CopyRemovingComments(FILE *in, FILE *out);

int main() {
  printf("BUG: komentarze w napisach /* takie jak ten */ też są usuwane.\n");
  CopyRemovingComments(stdin, stdout);
}

void CopyRemovingComments(FILE *in, FILE *out) {
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
        nc = fgetc(in);
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
