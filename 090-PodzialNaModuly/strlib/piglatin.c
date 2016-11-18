
#include <ctype.h>

#include "strlib.h"
#include "piglatin.h"

/*
 * Function: FindFirstVowel
 * Usage: k = FindFirstVowel(word);
 * --------------------------------
 * FindFirstVowel returns the index position of the first vowel
 * in word.  If word does not contain a vowel, FindFirstVowel
 * returns -1.
 */

static int FindFirstVowel(string word);

/*
 * Function: IsVowel
 * Usage: if (IsVowel(ch)) . . .
 * -----------------------------
 * IsVowel returns TRUE if ch is a vowel.  This function
 * recognizes vowels in either upper or lower case.
 */

static bool IsVowel(char ch);


string TranslateWord(string word)
{
    int vp;
    string head, tail;

    vp = FindFirstVowel(word);
    if (vp == -1) {
        return (word);
    } else if (vp == 0) {
        return (Concat(word, "way"));
    } else {
        head = SubString(word, 0, vp - 1);
        tail = SubString(word, vp, StringLength(word) - 1);
        return (Concat(tail, Concat(head, "ay")));
    }
}


static int FindFirstVowel(string word)
{
    int i;

    for (i = 0; i < StringLength(word); i++) {
        if (IsVowel(IthChar(word, i))) return (i);
    }
    return (-1);
}


static bool IsVowel(char ch)
{
    switch (tolower(ch)) {
      case 'a': case 'e': case 'i': case 'o': case 'u':
        return (TRUE);
      default:
        return (FALSE);
    }
}
