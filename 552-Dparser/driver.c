
#include <stdio.h>
#include <string.h>
#include <dparse.h>

extern D_ParserTables parser_tables_gram;

char *sbuf_read(char *pathname);

int main(int argc, char *argv[]) {
  char *buf;
  D_ParseNode *pn;
  D_Parser *p = new_D_Parser(&parser_tables_gram, 0);
  p->save_parse_tree = 1;

  if (argc!=2) {
    fprintf(stderr,"U¿ycie:   %s plik_z_tekstem_do_analizy_sk³adniowej\n", argv[0]);
    fprintf(stderr,"Przyk³ad: %s %s.test.g.1\n",argv[0],argv[0]);
    return -1;
  } else {
    buf = sbuf_read(argv[1]);
    if (buf == NULL) {
      fprintf(stderr, "error: empty buf\n");
      return -2;
    }
  }
  printf("parsing file %s\n--------------------------------\n%s", argv[1],buf);
  printf("--------------------------------\n");
  if ((pn=dparse(p, buf, strlen(buf))) && !p->syntax_errors)
    printf("\nsuccess\n");
  else
    printf("\nfailure\n");

  return 0;
}

