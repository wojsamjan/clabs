/* $Source: /home/nls/WEB/zjp/XX-Lib/RCS/symtab.c,v $
   $Date: 2000/01/21 11:21:53 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This file implements the symbol table abstraction. 
 */

#include <stdio.h>
#include <limits.h>
#include "symtab.h"
#include "genlib.h" /* |UNDEFINED| */

/* Number of buckets in the hash table; should be prime */
#define hash_size 353

/* This type defines a linked list cell for the symbol table. */
typedef struct cellT {
  char *key;
  void *value;
  struct cellT *link;
} cellT;

/* This type defines the underlying concrete representation for
   a |symtabADT|. These details are not relevant to and therefore 
   not exported to the client. In this implementation, the underlying
   structure is a hash table organized as an array of ``buckets'',
   in which each bucket is a linked list of elements that share
   the same code. */

struct symtabCDT {
  cellT *buckets[hash_size];
  unsigned int nhits[hash_size];
};

/* Private function declarations. */

static void free_bucket_chain(cellT *cp);
static cellT *find_cell(cellT *cp, char *key);
static int hash(unsigned char *s);

/* Public entries. */

char *xstrdup(char *s);

symtabADT new_symbol_table(void) {
  symtabADT t;
  int i;
  t=New(symtabADT);
  for (i=0; i<hash_size; i++) t->buckets[i]=NULL;
  return t;
}

void free_symbol_table(symtabADT table) {
  int i;
  for (i=0; i<hash_size; i++) free_bucket_chain(table->buckets[i]);
  FreeBlock(table);
}

void enter(symtabADT table, char *key, void *value) {
  int bucket;
  cellT *cp;
  bucket=hash(key);
  cp=find_cell(table->buckets[bucket],key);
  if (cp==NULL) {
    cp=New(cellT *);
    cp->key=xstrdup(key);
    cp->link=table->buckets[bucket];
    table->buckets[bucket]=cp;
    table->nhits[bucket]++;
  }
  cp->value=value;
}

void *lookup(symtabADT table, char *key) {
  int bucket;
  cellT *cp;
  bucket=hash(key);
  cp=find_cell(table->buckets[bucket],key);
  if (cp==NULL) return UNDEFINED;
  return cp->value;
}

void map_symbol_table(symtabFnT fn, symtabADT table, void *clientData) {
  int i;
  cellT *cp;
  for (i=0; i<hash_size; i++) 
    for (cp=table->buckets[i]; cp!=NULL; cp=cp->link)
      fn(cp->key, cp->value, clientData);
}

/* Private functions. */

/* This function takes a chain pointer and frees all the cells
   in that chain. Because the package makes copies of the keys,
   this function must free the string storage as well. */
static void free_bucket_chain(cellT *cp) {
  cellT *next;
  while (cp!=NULL) {
    next=cp->link;
    FreeBlock(cp->key);
    FreeBlock(cp);
    cp=next;
  }
}

/* This function finds a cell in the chain beginning at |cp| that
   matches a |key|. If a match is found, a pointer to that cell is
   returned. If no match is found, the function returns |NULL|. */

static cellT *find_cell(cellT *cp, char *key) {
  while (cp!=NULL && strcmp(cp->key,key)!=0) 
    cp=cp->link;
  return cp;
}

/* This function takes the key and uses it to derive a hash code,
   which is an integer in the range [0,hash_size). The hash
   code is copied from section 36 of common.w (from CWEB package).
   The choice of the value for |hash_size| can have a significant 
   effect on the performance of the algorithm, but not its correctnes. */

static int hash(unsigned char *s) {
  unsigned char *i=s;
  unsigned long h=0;
  while (*i++!='\0') h=(h+h+((unsigned int) *i)) % hash_size;
  return h;
}

void show_symbol_table(symtabADT table) {
  int i;
  unsigned int max_hits=0, min_hits=INT_MAX;
  printf("Distribution of keys in sym_table[%d].",hash_size);
  for (i=0; i<hash_size; i++) {
    int nhits=table->nhits[i];
    if (max_hits<nhits) max_hits=nhits;
    if (min_hits>nhits) min_hits=nhits;
    if (i%10==0) fprintf(stderr,"\n%3d: ",i);
    fprintf(stderr,"%7d",table->nhits[i]);
  }
  fprintf(stderr,"\nmin hits: %d, max hits: %d\n",min_hits,max_hits);
}

/* This function copies the string |s| into dynamically 
   allocated storage and returns the new string. */
char *xstrdup(char *s) {
  return strcpy(GetBlock(strlen(s)+1),s);
}
