
#include <ctype.h>

#include "string.h"
#include "piglatin.h"

#include "genlib.h"

/*
 * Function: FindFirstVowel
 * Usage: vp = FindFirstVowel(word);
 * --------------------------------
 * FindFirstVowel returns the index position of the first vowel
 * in word.  If word does not contain a vowel, FindFirstVowel
 * returns NULL.
 */

static char *FindFirstVowel(char *word);

/*
 * Function: IsVowel
 * Usage: if (IsVowel(ch)) . . .
 * -----------------------------
 * IsVowel returns TRUE if ch is a vowel.  This function
 * recognizes vowels in either upper or lower case.
 */

static int IsVowel(char ch);


void TranslateWord(char *word, char buffer[], int bufferSize) {
  char *vp;
  int wordLength;
  
  vp=FindFirstVowel(word);
  wordLength=strlen(word);
  if (vp==word)
    wordLength += 3;
  else if (vp!=NULL)
    wordLength += 2;
  if (wordLength>bufferSize) 
    Error("Buffer overflow");
  if (vp==NULL) 
    strcpy(buffer,word);
  else if (vp==word) {
    strcpy(buffer,word);
    strcat(buffer,"way");
  } else {
    strcat(buffer,vp);
    strncat(buffer,word,vp-word);
    strcat(buffer,"ay");
  }
}


static char *FindFirstVowel(char *word) {
  char *cp;
  for (cp=word; *cp!='\0'; cp++) {
    if (IsVowel(*cp))
      return (cp);
  }
  return (NULL);
}


static int IsVowel(char ch)
{
    switch (tolower(ch)) {
      case 'a': case 'e': case 'i': case 'o': case 'u':
        return (1);
      default:
        return (0);
    }
}
