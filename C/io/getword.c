#include <stdio.h>

int getword(char *word, int limit, int (*char_comp)(int))
{
    int c;
    char *w = word;

    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n')
        return '\n';
    ungetc(c, stdin);
    while (!(*char_comp)(c = getchar()) && c != EOF && c != '\n');
    if (c != EOF)
        *w++ = c;
    if (!(*char_comp)(c)) {
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

