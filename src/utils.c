#include <stdio.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "manage.h"
#include "info.h"

extern LPHASH user;
extern LinkedList current_car_list;
extern LinkedList current_list;

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

int getDateTime(char *datetime){
    struct tm* today;
    time_t rawTime = time(NULL);
    today = localtime(&rawTime);  

    sprintf(datetime, "%4d-%02d-%02d %02d:%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday,
        today->tm_hour, today->tm_min
    );
	return OK;
}

int getTodayDate(char *datetime){
	struct tm* today;
    time_t rawTime = time(NULL);
    today = localtime(&rawTime);  

    sprintf(datetime, "%4d-%02d-%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday
    );
	return OK;
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

	return OK;
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
	return OK;
}


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


int printUserData(void){
	FILE *fp = fopen(USER_DATA_FILE_PATH, "rb");
	printf("name\tcar_num\tphone_num\trecentTicket\thas_ticket\n");
	while (1) {
		USER_INFO tmp;
		fread(&tmp, sizeof(USER_INFO), 1, fp);
		if (feof(fp)) break;
		printf("%s\t%s\t%s\t%s\t%d\n", 
			tmp.name, tmp.car_num, tmp.phone_num,
			tmp.recentTicket, tmp.has_ticket
		);
	}
	fclose(fp);
}
int printCurrentData(void){
	FILE *fp = fopen(CURRENT_DATA_FILE_PATH, "rb");
	printf("car_number\tcar_type\tfloor\tin_datetime\tout_datetime\tfee\tis_paid\n");
	while (1) {
		CAR_INFO tmp;
		fread(&tmp, sizeof(CAR_INFO), 1, fp);
		if (feof(fp)) break;
		printf("%s\t%c\t%d\t%s\t%s\t%d\t%d\n", 
			tmp.car_number, tmp.car_type, tmp.floor,
			tmp.in_datetime, tmp.out_datetime,
			tmp.fee, tmp.is_paid
		);
	}
	fclose(fp);
}
int printHistoryData(void){
	FILE *fp = fopen(HISTORY_DATA_FILE_PATH, "rb");
	printf("car_number\tcar_type\tfloor\tin_datetime\tout_datetime\tfee\tis_paid\n");
	while (1) {
		CAR_INFO tmp;
		fread(&tmp, sizeof(CAR_INFO), 1, fp);
		if (feof(fp)) break;
		printf("%s\t%c\t%d\t%s\t%s\t%d\t%d\n", 
			tmp.car_number, tmp.car_type, tmp.floor,
			tmp.in_datetime, tmp.out_datetime,
			tmp.fee, tmp.is_paid
		);
	}
	fclose(fp);
}
int printParkingLotData(void){
	FILE *fp = fopen(PARKINGLOT_SETTINGS_FILE_PATH, "rb");
	
	printf("floor\ttotal\ttotal_car\telectric_charge\thandicapped\tlight_car\n");
	while (1) {
		PARK tmp;
		fread(&tmp, sizeof(PARK), 1, fp);
		if (feof(fp)) break;
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
			tmp.floor, tmp.total, tmp.total_car, 
			tmp.electric_charge, tmp.handicapped, tmp.light_car
		);
	}
	fclose(fp);
}


int printCurrentParkList(void){
	printf("floor\ttotal\ttotal_car\telectric_charge\thandicapped\tlight_car\n");
	
	Node* cur;
	cur = current_list.head;
	while (cur) {
		PARK* tmp = (PARK*) cur->data;
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
			tmp->floor, tmp->total, tmp->total_car, 
			tmp->electric_charge, tmp->handicapped, tmp->light_car
		);
	}

}
int printCurrentCarList(void){
	printf("car_number\tcar_type\tfloor\tin_datetime\tout_datetime\tfee\tis_paid\n");

	Node* cur;
	cur = current_car_list.head;
	while (cur){
		CAR_INFO* tmp;
		tmp = (CAR_INFO*) cur->data;
		printf("%s\t%c\t%d\t%s\t%s\t%d\t%d\n", 
			tmp->car_number, tmp->car_type, tmp->floor,
			tmp->in_datetime, tmp->out_datetime,
			tmp->fee, tmp->is_paid
		);
		cur = cur->next;
	}
}