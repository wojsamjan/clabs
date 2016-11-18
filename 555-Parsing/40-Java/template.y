%{
/* $Source: /home/nls/WEB/zjp/40-Java/RCS/template.y,v $
   $Date: 2000/03/28 16:50:02 $
   $Revision: 1.1 $

   This file is distributed WITHOUT ANY WARRANTY, express or implied.
   Copyright (C) 2000 Wlodek Bzyl
 
   Template file for testing conflicts in grammars.

   To identify shift/reduce conflict:
   (1) find the shift/reduce error in *.output
   (2) pick out the reduce rule
   (3) pick out the relevant shift rules
   (4) see where the reduce rule reduces to
   (5) deduce the token stream that will produce the conflict
 */
%}
%token ?
%%
start: ?
%%
