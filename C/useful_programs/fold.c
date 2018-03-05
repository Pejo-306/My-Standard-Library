#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_CONST 80
#define INDENT_SIZE 4

char *getline(int);
int get_indent_scope(char *, int);
int line_leftovers(char *, int, int);
char **fold_line(char *, int, int, int);

int main()
{
    char *line;
    char **segments;
    while ((line = getline(LINE_CONST)) != NULL) {
        segments = fold_line(line, LINE_CONST, INDENT_SIZE, 1);
        if (segments != NULL)
            for (int l = 0; segments[l] != NULL; ++l)
                printf("%s", segments[l]);
        else
            printf("%s", line);
    }

    free(line);
    free(segments);

    return 0;
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

int get_indent_scope(char *line, int indent_size)
{
    int i;
    for (i = 0; line[i] == ' '; ++i);

    if (i % indent_size)
        // error: line is not indented by indent_size
        return -1;
    return i / indent_size;
}

int line_leftovers(char *line, int offset, int use_punct)
{
    int leftovers = 0;
    while (isalpha(line[offset-leftovers]) ||
            (ispunct(line[offset-leftovers]) && (use_punct != 0)))
        leftovers++;
    return leftovers;
}

char **fold_line(char *line, int max_length, int indent_size, int use_punct)
{
    int indentation = (get_indent_scope(line, indent_size) + 1) * indent_size;
    int lines_count = 0;
    int characters = strlen(line) - indentation;
    do {
        characters -= max_length - indentation;
        lines_count += 1;
    } while (characters > 0);

    char **segments = (char **)malloc(sizeof(char *) * (lines_count + 1));
    segments[lines_count] = NULL; // the end of the string array

    int leftovers = 0, total_offsets = 0;
    for (int l = 0, offset = 0; l < lines_count; ++l) {
        segments[l] = (char *)malloc(sizeof(char) * (max_length+2));
        memset(segments[l], ' ', sizeof(char) * max_length+1);
        segments[l][max_length] = '\n';
        segments[l][max_length+1] = '\0';

        leftovers = line_leftovers(line,
            offset + max_length - indentation * (l != 0), use_punct);
        total_offsets += leftovers + indentation * (l != 0);

        for (int i = 0; i < max_length - indentation * (l != 0) - leftovers; ++i)
            segments[l][indentation * (l != 0) + i] = line[offset * (l != 0) + i];

        offset += max_length - indentation * (l != 0) - leftovers;

        if (total_offsets > strlen(line)) {
            // line cannot be presented via the given length
            free(segments);
            if (use_punct) // attempt to fold without punctuation
                return fold_line(line, max_length, indent_size, 0);
            return NULL;
        }

        if (l == lines_count - 1 && offset < strlen(line)) {
            // more string segments are required to fold the line
            lines_count++;
            segments = (char **)realloc(segments, sizeof(char *) * (lines_count + 1));
            segments[lines_count] = NULL; // the end of the string array
        }
    }
    
    return segments;
}

