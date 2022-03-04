#if !defined(__HISTORY_DETAIL_H__)
#define __HISTORY_DETAIL_H__

#include "widget.h"
#include <string.h>
#define BY_CAR_NUMBER 1
#define BY_NOT_PAID 2
#define BY_DATE_IN 3
#define BY_DATE_OUT 4

typedef Widget HISTORY_DETAIL_UI;

HISTORY_DETAIL_UI* createHistoryDetailUI(int type); 
Widget* createHistoryDetailSub();


int renderHistoryDetail(HISTORY_DETAIL_UI* history, int type);


int getHistoryDetail(int type, char* data, LPARRAY* datas);

#endif // __HISTORY_DETAIL_H__
