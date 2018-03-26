#include <ctype.h>
#include "vartype.h"
#include "input.h"

int iscvarname(char *str)
{
    int c, result = 0;

    while (isspace(*str) || *str == '*' || *str == '&')
        str++;
    if (isalpha(*str)) {
        if ((c = getch()) != '(')
            result = 1;
        ungetch(c);
    }
    return result;
}

int iscvarnamechar(int c)
{
    return (iswordchar(c) || c == '*' || c == '&' || c == '[' || c == ']') ? 1 : 0;
}

int iswordchar(int c)
{
    return (isalnum(c) || c == '_') ? 1 : 0;
}

