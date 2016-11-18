#!/bin/ch
#include <cgi.h>

int main() {
  int i, num;
  chstrarray name, value;
  class CResponse Response;
  class CRequest Request;
  class CServer Server;

  num=Request.getFormNameValue(name,value);
  Response.setContentType("text/html");
  Response.setCharSet("iso-8859-2");
  Response.begin();
  Response.title("Wykres");
  printf("<center>\n");
  printf("<img src=\"webplot2.ch");
  for (i=0; i<num; i++) {
    putc(i==0 ? '?' : '&', stdout);
    fputs(Server.URLEncode(name[i]),stdout);
    putc('=',stdout);
    fputs(Server.URLEncode(value[i]),stdout);
  }
  printf("\">\n");
  printf("</center>\n");
  Response.end();
}
