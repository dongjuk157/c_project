#if !defined(__PARKSTATUS_DETAIL_H__)
#define __PARKSTATUS_DETAIL_H__
#include "widget.h"

typedef Widget PARK_DETAIL_UI;

PARK_DETAIL_UI* createParkDetailEntryUI(); 
PARK_DETAIL_UI* createParkDetailFloorUI();
PARK_DETAIL_UI* createParkDetailOtherUI();

int renderDetailEntry(PARK_DETAIL_UI* park_detail);
int renderDetailFloor(PARK_DETAIL_UI* park_detail);
int renderDetailOther(PARK_DETAIL_UI* park_detail);


#endif // __PARKSTATUS_DETAIL_H__
