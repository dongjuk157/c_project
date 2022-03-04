#ifndef PARKSTATUS_UI_H
#define PARKSTATUS_UI_H
#include "widget.h"

#define PARK_STATUS_ENTRY 1
#define PARK_STATUS_FLOOR 2
#define PARK_STATUS_OTHER 3


typedef Widget PARKSTATUS_UI;

PARKSTATUS_UI* createParkStatusUI();
int renderParkStatusUI(PARKSTATUS_UI *parkStatus_UI, void* data);

#endif // PARKSTATUS_UI_H
