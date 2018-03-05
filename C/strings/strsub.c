#include <stdlib.h>
#include <string.h>

#define REPLACES 4

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

