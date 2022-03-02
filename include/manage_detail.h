#if !defined(__MANAGE_DETAIL_H__)
#define __MANAGE_DETAIL_H__

#include "widget.h"

#define IN_CAR 'i'
#define OUT_CAR 'o'

typedef Widget MANAGE_DETAIL_UI;

MANAGE_DETAIL_UI* createManageDetailUI(char io);

#endif // __MANAGE_DETAIL_H__
