#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include "utils.h"

void gotoxy(int x, int y)
{
    printf("\033[%dd\033[%dG",y,x);
}

// int kbhit(void)
// {
// 	struct termios oldt, newt;
// 	int ch;
// 	tcgetattr(STDIN_FILENO, &oldt);
// 	newt = oldt;
// 	newt.c_lflag &= ~(ICANON | ECHO);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
// 	ch = getchar();
// 	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
// 	return ch;
// }



int getch(void) 
{
	int ch;
	struct termios buf, save;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}

int min(int a, int b){
	return (a<b) ? a : b;
}