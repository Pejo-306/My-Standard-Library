#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_CONST 80
#define REPLACES    4

int strsub(char *, char *, char *);
char *getline(int);
void entab(char *, int);

int main(int argc, char **argv)
{
    int columns = atoi(argv[1]);

    char *line;
    while ((line = getline(LINE_CONST)) != NULL) {
        entab(line, columns);
        printf("%s", line);
    }
    free(line);

    return 0;
}

int strsub(char *str, char *search, char *replace)
{
    char *buffer = (char *)malloc(sizeof(char) *
        (strlen(str)+1 + REPLACES * (strlen(replace)-1)));
    int substitutions = 0;
    int buffer_i = 0;
    for (int str_i = 0, j; str_i < strlen(str); str_i++) {
        for (j = 0; j < strlen(search) && str[str_i+j] == search[j]; ++j);

        if (j == strlen(search)) { // match found
            for (int c = 0; c < strlen(replace); ++c)
                buffer[buffer_i+c] = replace[c];
            buffer_i += strlen(replace);
            str_i += strlen(search) - 1;
            substitutions++;

            if (substitutions % REPLACES == 0)
                // allocate more memory
                buffer = (char *)realloc(buffer, sizeof(char) *
                    (strlen(str)+1 + strlen(buffer)+1 + REPLACES * (strlen(replace)-1)));
        } else {
            buffer[buffer_i] = str[str_i];
            buffer_i++;
        }
    }
    buffer[buffer_i] = '\0';

    if (substitutions > REPLACES)
        // additional memory has been allocated
        str = (char *)realloc(str, sizeof(char) * strlen(buffer)+1);
    strcpy(str, buffer);
    free(buffer);

    return substitutions;
}

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

void entab(char *line, int columns)
{
    char *indentation = (char *)malloc(sizeof(char) * (columns + 1));
    memset(indentation, ' ', sizeof(char) * columns);
	indentation[columns] = '\0';
    strsub(line, indentation, "\t");
    free(indentation);
}

