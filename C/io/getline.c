#include <stdlib.h>
#include <string.h>

char *getline(int);

char *getline(int limit)
{
    char *line = (char *)malloc(sizeof(char) * limit);
    int c, i;
    int offset = 0;

    do {
        for (i = offset; i < limit-1 && (c = getchar()) != EOF && c != '\n'; ++i)
            line[i] = c;

        offset = strlen(line); 
        limit *= 2;
        line = (char *)realloc(line, sizeof(char) * limit);
    } while (i == limit / 2 - 1);

    line[i] = '\n';
    line[i+1] = '\0';

    if (c == EOF)
        return NULL; 
    return line;
}

