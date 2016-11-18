/* $Source: /home/nls/WEB/zjp/09-MultiCalc/RCS/symtab.h,v $
   $Date: 2000/01/08 14:09:24 $
   $Revision: 1.2 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl

   This interface exports a simple symbol table abstraction. 
 */

#ifndef _symtab_h
#define _symtab_h

/* This type is the abstract data type used to represent 
   a symbol table. */
typedef struct symtabCDT *symtabADT;

/* This type defines the class of functions that can be used to
   map over the entries in a symbol table. */
typedef void (*symtabFnT)(char *key, void *value, void *clientData);

/* This function allocates a new symbol table without entries. */
symtabADT new_symbol_table(void);

/* This function frees the storage associated with the symbol table. */
void free_symbol_table(symtabADT table);

/* This function associates key with value in the symbol table.
   Each call to |enter| supersedes any previous definition for key. */
void enter(symtabADT table, char *key, void *value);

/* This function returns the value associated with key in the symbol
   table, or |UNDEFINED|, if no such value exists. */
void *lookup(symtabADT table, char *key);

/* This function goes through every entry in the symbol table
   and calls the function |f|, passing it the following arguments:
   the current key, its associated |value|, and the |clientData|
   pointer. The |clientData| pointer allows the client to pass 
   additional state information to the function |f|, if necessary. 
   If no |clientData| argument is appropriate, this value should be |NULL|. */
void map_symbol_table(symtabFnT fn, symtabADT table, void *clientData);

/* This function shows the distribution of keys inserted into hash table.
   The only purpose of |show_symbol_table| is to debug function used 
   for hashing. You should not use this function in your programs. */
void show_symbol_table(symtabADT table);

#endif
