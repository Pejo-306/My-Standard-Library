#include <stdio.h>
#include <string.h>
#include "input.h"
#include "vartype.h"

#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET  "\x1b[0m"
#define MAXWORD       100
#define MAXIDENTIFIERS 10
#define NKEYS (sizeof identifiers / sizeof identifiers[0])

char *identifiers[] = {
    "auto",
    "char",
    "const",
    "double",
    "extern",
    "float",
    "int",
    "long",
    "register",
    "short",
    "signed",
    "static",
    "struct",
    "union",
    "unsigned",
    "void",
    "volatile"
};
char struct_name[MAXWORD];

char *binsearch(char *, char **, int);
void print_declaration(int, char **, int, char *);

int main(void)
{
    int c, nlines;
    int processing_varname;
    int identifiers_count;
    char word[MAXWORD];
    char *identifier;
    char *var_declaration[MAXIDENTIFIERS];

    processing_varname = 0;
    identifiers_count = 0;
    nlines = 1;
    while ((c = getword(word, MAXWORD, iscvarnamechar)) != EOF) {
        if (c == '\n')
            nlines++;
        if (iscvarname(word)) {
            if ((identifier = binsearch(word, identifiers, NKEYS)) != NULL &&
                    identifiers_count < MAXIDENTIFIERS) {
                var_declaration[identifiers_count++] = identifier;
                processing_varname = 1;

                if (strcmp(identifier, "struct") == 0 ||
                        strcmp(identifier, "union") == 0) {
                    // write struct name
                    getword(struct_name, MAXWORD, iscvarnamechar);
                    var_declaration[identifiers_count++] = struct_name;
                }
            } else if (processing_varname == 1) {
                print_declaration(nlines, var_declaration, identifiers_count, word);
                identifiers_count = 0;
                processing_varname = 0;
                struct_name[0] = '\0';
            }
        } else {
            if (strlen(struct_name) > 0) {
                struct_name[0] = '\0';
                while (getch() != '}');
            }

            identifiers_count = 0;
            processing_varname = 0;
        }
    }
    return 0;
}

char *binsearch(char *word, char **identifiers, int size)
{
    int cond;
    char **low = identifiers;
    char **high = identifiers+size;
    char **mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        cond = strcmp(word, *mid);
        if (cond < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return *mid;
    }
    return NULL;
}

void print_declaration(int line_number, char **identfs, int count, char *varname)
{
    // line number
    printf(ANSI_COLOR_YELLOW "%4d: " ANSI_COLOR_RESET, line_number);
    // variable identifiers
    for (int i = 0; i < count; ++i) {
        printf(ANSI_COLOR_GREEN);
        printf("%s ", identfs[i]);
        printf(ANSI_COLOR_RESET);
    }
    // variable name
    printf("%s\n", varname);
}

