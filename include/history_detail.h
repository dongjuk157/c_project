#if !defined(__HISTORY_DETAIL_H__)
#define __HISTORY_DETAIL_H__

#include "widget.h"
#include <string.h>
#define BY_CAR_NUMBER 1
#define BY_NOT_PAID 2
#define BY_DATE_IN 3
#define BY_DATE_OUT 4

typedef Widget HISTORY_DETAIL_UI;

struct car_information{
    char car_number[20]; // 123가4567 
    char in_datetime[20]; // 2022-02-28 21:44:42 : \0까지 해서 20자리
    char out_datetime[20];
    char car_type; // [e]lectric, [l]ight, [n]ormal
    char is_paid; // when creating
    int floor; // except 0
    int fee; // when creating, 0
};

HISTORY_DETAIL_UI* createHistoryDetailUI(int type); 
Widget* createHistoryDetailSub();


int renderHistoryDetail(HISTORY_DETAIL_UI* history, int type);


int getHistoryDetail(int type, char* data, LPARRAY* datas);

#endif // __HISTORY_DETAIL_H__
