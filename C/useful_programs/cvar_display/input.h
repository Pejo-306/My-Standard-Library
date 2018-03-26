#ifndef INPUT_H
#define INPUT_H

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getword(char *, int, int (*)(int));

#endif

