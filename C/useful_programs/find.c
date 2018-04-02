#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAXLINE  1024
#define LINE_WIDTH 80

int main(int argc, char *argv[])
{
    char *program = argv[0];
    register int c, lineno, i;
    int number = 0, found = 0, highlight = 0, filename = 0;
    char line[MAXLINE];
    char *pattern, *substr_beginning, *sp;
    FILE *fp;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                number = 1;
                break;
            case 'h':
                highlight = 1;
                break;
            case 'f':
                filename = 1;
                break;
            default:
                fprintf(stderr, "%s: illegal option %c\n", program, c);
                puts("Usage: find -x -n pattern file1, [file2, ...]");
                exit(-1);
            }
        }
    }
    if (argc == 0) {
        fprintf(stderr, "%s: no pattern provided\n", program);
        puts("Usage: find -x -n pattern file1, [file2, ...]");
        exit(-4);
    } else if (argc == 1) {
        fprintf(stderr, "%s: no files provided\n", program);
        puts("Usage: find -x -n pattern file1, [file2, ...]");
        exit(-5);
    }
    pattern = (*argv)++;

    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", program, *argv);
            exit(-3);
        } else {
            if (filename) {
                for (i = 0; i < (LINE_WIDTH - strlen(*argv)) / 2; ++i)
                    putchar('=');
                if (highlight)
                    printf(ANSI_COLOR_YELLOW);
                printf("%s", *argv);
                if (highlight)
                    printf(ANSI_COLOR_RESET);
                for (i = 0; i < (LINE_WIDTH - strlen(*argv)) / 2; ++i)
                    putchar('=');
                putchar('\n');
            }

            for (lineno = 1; fgets(line, MAXLINE, fp) != NULL; ++lineno) {
                if ((substr_beginning = strstr(line, pattern)) != NULL) {
                    if (number) {
                        if (highlight)
                            printf(ANSI_COLOR_YELLOW);
                        printf("%d: ", lineno);
                        if (highlight)
                            printf(ANSI_COLOR_RESET);
                    }

                    for (sp = line; sp < substr_beginning; ++sp)
                        putchar(*sp);
                    if (highlight)
                        printf(ANSI_COLOR_GREEN);
                    for (i = 0; i < strlen(pattern); ++i)
                        putchar(*(sp+i));
                    if (highlight)
                        printf(ANSI_COLOR_RESET);
                    for (sp += strlen(pattern); *sp; ++sp)
                        putchar(*sp);
                    found++;
                }
            }
            fclose(fp);
        }
    }

    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", program);
        exit(-2);
    }
    return found;
}

