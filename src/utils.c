#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include "utils.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>


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
// int date[] = {0,0,31,59,90,120,151,181,212,243,273,304,334,365};
int calculate_fee(char* inDateTime, char* outDateTime){
    int inYear,outYear;
    int inMon,outMon;
    int inDay,outDay;
    int inHour,outHour;
    int inMin,outMin;
    //2022-02-10 20:22
    //0123456789123456
    inYear = atoi(inDateTime);
    outYear = atoi(outDateTime);

    inMon = atoi(&inDateTime[5]);
    outMon = atoi(&outDateTime[5]);

    inDay = atoi(&inDateTime[8]);
    outDay = atoi(&outDateTime[8]);

    inHour = atoi(&inDateTime[11]);
    outHour = atoi(&outDateTime[11]);

    inMin = atoi(&inDateTime[14]);
    outMin = atoi(&outDateTime[14]);

	int diffDay = diff(inYear,inMon,inDay,outYear,outMon,outDay);

	int diffMin = diffDay*1440;
	diffMin += (outHour-inHour)*60 + (outMin - inMin);

	int fee = diffMin / 10 * 100;
	fee += (diffMin % 10) ? 100 : 0;

	printf("%d",fee);
	return fee;
}
int to_day(int y, int m, int d)
{
	int mon[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int day = 0;
	int i;
	for(i=1; i<y; i++){
		day += ((i%4==0 && i%100!=0) || i%400==0)? 366 : 365;
	}
	if((y%4==0 && y%100!=0) || y%400==0) mon[2]++;
	for(i=1; i<m; i++){
		day += mon[i];
	}
	return day + d;
}
int diff(int y1, int m1, int d1, int y2, int m2, int d2)
{
	int a = to_day(y1, m1, d1);
	int b = to_day(y2, m2, d2);
	return b-a;
}
