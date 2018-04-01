#include <stdio.h>

int getword(char *word, int limit, int (*char_comp)(int))
{
    int c;
    char *w = word;

    while (isspace(c = getchar()));
    if (c != EOF)
        *w++ = c;
    if (!(*char_comp)(c) && c != '#') {
        *w = '\0';
        return c;
    }
    for ( ; --limit > 0; w++) {
        if (!(*char_comp)(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

