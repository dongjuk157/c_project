#if !defined(__UTILS_H__)
#define __UTILS_H__
#define False 0
#define True 1
typedef char bool;
void gotoxy(int x, int y);
int min(int a, int b);
// int kbhit(void);
int getch(void);
int to_day(int y, int m, int d);
int diff(int y1, int m1, int d1, int y2, int m2, int d2);
int calulate_fee(char* inDateTime, char* outDateTime);

#endif // __UTILS_H__
