#if !defined(__PARKSTATUS_DETAIL_H__)
#define __PARKSTATUS_DETAIL_H__
#include "widget.h"

typedef Widget PARK_DETAIL;

HISTORY_DETAIL_UI* createHistoryDetailUI(int type); 
Widget* createHistoryDetailSub();

#endif // __PARKSTATUS_DETAIL_H__
