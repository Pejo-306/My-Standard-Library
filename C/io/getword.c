#include <stdio.h>
#include "getch.h"

int getword(char *word, int lim, int (*char_comp)(int))
{
    int c;
    char *w = word;

    while ((c = getch()) == ' ' || c == '\t');
    if (c != EOF)
        *w++ = c;
    if (!(*char_comp)(c) && c != '#') {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!(*char_comp)(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

