#if !defined(__UTILS_H__)
#define __UTILS_H__
#define False 0
#define True 1

#define OK 0
typedef char bool;
void gotoxy(int x, int y);
int min(int a, int b);
// int kbhit(void);
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

#endif // __UTILS_H__
