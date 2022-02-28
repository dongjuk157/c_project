#if !defined(__HISTORY_H__)
#define __HISTORY_H__

#include "widget.h"

typedef Widget HISTORY_UI;

HISTORY_UI* createHistoryUI(); 

int renderHistoryUI(HISTORY_UI* history);

#endif // __HISTORY_H__
