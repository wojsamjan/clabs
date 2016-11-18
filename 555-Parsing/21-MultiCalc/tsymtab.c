/* ----------------------------------------------------------
   $Source: /home/nls/WEB/mfcalc/RCS/tsymtab.c,v $
   $Date: 1999/12/30 21:52:28 $
   $Revision: 1.2 $
   ----------------------------------------------------------
   This Makefile belongs to the MFCALC package.
   It is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
   ----------------------------------------------------------
   This file tests the implementation of the symbol table.
 */

#include <stdio.h>
#include <string.h>
#include "genlib.h"
#include "symtab.h"

typedef struct {
  int count;
} *counterT;

static char buffer[128];

static void dump_entry(string key, void *value, void *clientData) {
  printf("%s\t%d\n", key, ((counterT) value)->count);
}

static void record_line(symtabADT t, string l) {
  counterT entry;
  entry=lookup(t,l);
  if (entry==UNDEFINED) {
    entry=New(counterT);
    entry->count=0;
    enter(t,l,entry);
  }
  entry->count++;
}

static void display_word_frequencies(symtabADT table) {
  printf("Word frequencies (significant 3 letters):\n");
  map_symbol_table(dump_entry,table,NULL);
}

int main() {
  symtabADT table=new_symbol_table();
  while (fgets(buffer,127,stdin)!=NULL) {
    buffer[127]='\0';
    record_line(table,buffer);
  }
  //  display_word_frequencies(table);
  show_symbol_table(table);
  return 0;
}
