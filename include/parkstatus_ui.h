#ifndef PARKSTATUS_UI_H
#define PARKSTATUS_UI_H
#include "widget.h"

typedef Widget PARKSTATUS_UI;

PARKSTATUS_UI* createParkStatusUI();
int renderParkStatusUI(PARKSTATUS_UI *parkStatus_UI);

#endif // PARKSTATUS_UI_H
