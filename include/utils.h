#if !defined(__UTILS_H__)
#define __UTILS_H__
#define False 0
#define True 1
#include <termios.h>
#include <sys/types.h>
#include <sys/select.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define UTILS_EOK 0

typedef int (*FP)(void*, void*);
typedef char bool;

struct termios buf, savebuf;


int gotoxy(int x, int y); 
int min(int a, int b);
int getch(void);
int to_day(int y, int m, int d);
int diff(int y1, int m1, int d1, int y2, int m2, int d2);
int calculate_fee(char* inDateTime, char* outDateTime);
int getDateTime(char *datetime);
int getTodayDate(char *datetime);
int getOneMonthAfterFromDate(char *date);
int getOneMonthAfterFromToday(char *date);

int printUserData(void);
int printCurrentData(void);
int printHistoryData(void);
int printParkingLotData(void);
int printCurrentParkList(void);
int printCurrentCarList(void);

#endif // __UTILS_H__
