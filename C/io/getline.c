#include <stdlib.h>
#include <string.h>

int getline(char *, int);

int getline(char *line, int limit)
{
    int c, i;
    int offset = 0;

    do {
        for (i = offset; i < limit-1 && (c = getchar()) != EOF && c != '\n'; ++i)
            line[i] = c;

        if (i == limit - 1) {
            offset = strlen(line); 
            limit *= 2;
            line = (char *)realloc(line, sizeof(char) * limit);
        }
    } while (i == limit / 2 - 1);
    line[i] = '\n';
    line[i+1] = '\0';

    return i;
}

