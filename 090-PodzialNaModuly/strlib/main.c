/*
 * File: piglatin.c
 * ----------------
 * This program translates a line of text from English
 * to Pig Latin.  The rules for forming Pig Latin words
 * are as follows:
 *
 * o  If the word begins with a vowel, add "way" to the
 *    end of the word. Example: any -> anyway
 *
 * o  If the word begins with a consonant, extract the set
 *    of consonants up to the first vowel, move that set
 *    of consonants to the end of the word, and add "ay".
 *    Example: trash -> ashtray 
*/

#include <stdio.h>
#include <ctype.h>

#include "genlib.h"
#include "strlib.h"
#include "simpio.h"
#include "scanner.h"

#include "piglatin.h"

static void TranslateLine(string line);
static bool IsLegalWord(string token);


int main()
{
    string line;

    printf("Enter a line: ");
    line = GetLine();
    TranslateLine(line);
    return 0;
}

/*
 * Function: TranslateLine
 * Usage: TranslateLine(line);
 * ---------------------------
 * This function takes a line of text and translates
 * the words in the line to Pig Latin, displaying the
 * translation as it goes.
 */

static void TranslateLine(string line)
{
    string token;

    InitScanner(line);
    while (!AtEndOfLine()) {
        token = GetNextToken();
        if (IsLegalWord(token)) token = TranslateWord(token);
        printf("%s", token);
    }
    printf("\n");
}

/*
 * Function: IsLegalWord
 * Usage: if (IsLegalWord(token)) ...
 * ----------------------------------
 * IsLegalWord returns TRUE if every character in the argument
 * token is alphabetic.
 */

static bool IsLegalWord(string token)
{
    int i;

    for (i = 0; i < StringLength(token); i++) {
        if (!isalpha(IthChar(token, i))) return (FALSE);
    }
    return (TRUE);
}

