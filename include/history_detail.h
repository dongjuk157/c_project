#if !defined(__HISTORY_DETAIL_H__)
#define __HISTORY_DETAIL_H__

#include "widget.h"
#define BY_CAR_NUMBER 1
#define BY_NOT_PAID 2
#define BY_DATE_IN 3
#define BY_DATE_OUT 4

typedef Widget HISTORY_DETAIL_UI;

HISTORY_DETAIL_UI* createHistoryDetailUI(int type); 
Widget* createHistoryDetailSub();


int renderHistoryDetailByCarNum(HISTORY_DETAIL_UI* history);
int renderHistoryDetailByNotPaid(HISTORY_DETAIL_UI* history);
int renderHistoryDetailByDate(HISTORY_DETAIL_UI* history);

#endif // __HISTORY_DETAIL_H__
