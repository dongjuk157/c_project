#include "utils.h"

#include "info.h"
#include "messagebox.h"

extern LPHASH user;
extern LinkedList current_car_list;
extern LinkedList current_list;

int myGetline(char *__restrict __s, int __n, FILE *__restrict __stream){
	fgets( __s, __n, __stream);
    __s[strlen(__s)-1] = '\0';
	return UTILS_EOK;
}

int gotoxy(int x, int y)
{
    printf("\033[%dd\033[%dG",y,x);
	return UTILS_EOK;
}

int getDateTime(char *datetime){
    struct tm* today;
    time_t rawTime = time(NULL);
    today = localtime(&rawTime);  

    sprintf(datetime, "%4d-%02d-%02d %02d:%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday,
        today->tm_hour, today->tm_min
    );
	return UTILS_EOK;
}

int getTodayDate(char *datetime){
	struct tm* today;
    time_t rawTime = time(NULL);
    today = localtime(&rawTime);  

    sprintf(datetime, "%4d-%02d-%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday
    );
	return UTILS_EOK;
}
//특정날짜 "0000-00-00" 입력 -> 30일뒤 날짜 계산해서 포맷
int getOneMonthAfterFromDate(char *date){
	
	int year, month, day;
	sscanf(date, "%4d-%02d-%02d", &year, &month, &day);

	struct tm t = {0};
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day + 30;
	mktime(&t);

	sprintf(date, "%4d-%02d-%02d", t.tm_year+1900, t.tm_mon + 1, t.tm_mday);

	return UTILS_EOK;
}
//오늘날짜 기준 30일뒤 계산해서 포맷
int getOneMonthAfterFromToday(char *date){
	
	time_t now;
	struct tm t;
	time(&now);
	t = *localtime(&now);
	t.tm_mday += 30;
	mktime(&t);

	sprintf(date, "%4d-%02d-%02d", t.tm_year+1900, t.tm_mon + 1, t.tm_mday);
	return UTILS_EOK;
}

int getch(void) 
{
	int ch;
	tcgetattr(0, &savebuf);
	buf = savebuf;
	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &savebuf);
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
