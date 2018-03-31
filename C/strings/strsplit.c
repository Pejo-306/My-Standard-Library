#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 40

char **strsplit(char *str, int delimiter)
{
    int j;
    int size, count, len;
    char **split_str;

    j = 0;
    size = 4;
    count = 0;
    len = WORD_SIZE;
    split_str = (char **)malloc(sizeof(char *) * (size+1));
    split_str[0]  = (char *)malloc(sizeof(char) * len);
    for (int i = 0; i < strlen(str); ++i, ++j) {
        if (str[i] == delimiter) {
            // finish work on current word
            split_str[count][j] = '\0';
            split_str[count] = (char *)realloc(split_str[count], sizeof(char) * (j+1));

            if (++count == size) {  // allocate more memory for more words
                size *= 2;
                split_str = (char **)realloc(split_str, sizeof(char *) * (size+1));
            }
            // setup next word
            j = -1;
            len = WORD_SIZE;
            split_str[count] = (char *)malloc(sizeof(char) * len);
        } else {
            if (j == len) {  // allocate more memory for longer word
                len *= 2;
                split_str[count] = (char *)realloc(split_str[count], sizeof(char) * len);
            }
            split_str[count][j] = str[i];
        }
    }

    split_str[count++][j] = '\0';  // complete last word 
    split_str[count] = NULL;  // add a terminating NULL pointer
    return split_str;
}

