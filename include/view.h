#ifndef VIEW_H
#define VIEW_H

#include "widget.h"
#include "info.h"

int printFeeView();
int printFeeDetailView(char *carNumber, int fee, int hasTicket);
int printSingleLineView(char *currentMenu, char *defaultText);

#endif